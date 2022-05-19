#include "mega/sccloudraid/mega.h"

// configuration file parser

const char* std_config_file = "sccr_config";
const char* std_local_config_file = "sccr_config.local";

string Config::daemonname;

Config config(std_config_file);
Config configLocal(std_local_config_file, &config);

bool IPv6::operator==(const IPv6 &ipv6) const
{
    return !memcmp(ip.s6_addr, ipv6.ip.s6_addr, sizeof(in6_addr));
}

bool IPv6::operator<(const IPv6 &ipv6) const
{
    return memcmp(ip.s6_addr, ipv6.ip.s6_addr, sizeof(in6_addr)) < 0;
}

IPv6::IPv6(const char* addr)
{
    if (inet_pton(AF_INET6, addr, ip.s6_addr) != 1)
    {
        memcpy(ip.s6_addr, "\0\0\0\0\0\0\0\0\0\0\xff\xff", 12);
        if (inet_pton(AF_INET, addr, ip.s6_addr+12) != 1) memset(ip.s6_addr, 0, sizeof(ip.s6_addr));
    }
}

IPv6::IPv6(in6_addr* addr)
{
    ip = *addr;
}

void IPv6::tostring(char* buf, socklen_t size) const
{
    if (inet_ntop(AF_INET6, ip.s6_addr, buf, size) < 0) strcpy(buf, "[invalid]");
}

char* Config::skipspace(char* ptr)
{
    for (;;)
    {
        if (!*ptr || *(unsigned char*)ptr > ' ') return ptr;
        ptr++;
    }
}

char* Config::findspace(char* ptr)
{
    for (;;)
    {
        if (!*ptr || *(unsigned char*)ptr <= ' ') return ptr;
        ptr++;
    }
}

char* Config::findlastspace(char* q)
{
    for (;;)
    {
        char* p;
        p  = findspace(q);
        q = skipspace(p);
        if (!*q) return p;
    }
}

vector<string> Config::split(const string& line)
{
   vector<string> words;
   for (char* s = (char*)line.c_str(); *s != 0; )
    {
        s = Config::skipspace(s);
        auto t = Config::findspace(s);
        if (t > s) words.emplace_back(s, t);
        s = t;
    }
    return words;
}

void Config::loadStandardFiles(const char* cdaemonname)
{
    const char* ptr;

    if ((ptr = strrchr(cdaemonname, '/'))) ptr++;
    else ptr = cdaemonname;

    daemonname = ptr;
    config.update(true);
    configLocal.update(true);
}

Config::Config(const char* cfilename, Config* p)
    : lastmtime(0)
    , lastcheck(0)
    , nameips(new stringip_map)
    , ipnames(new ipstring_map)
    , settings(new settings_map)
    , filename(cfilename ? cfilename : std_config_file)
    , parent(p)
{
    cout << "Loading config from " << filename << endl;
}

// these prevent clang leak detection
stringip_map* noleak_nameips;
ipstring_map* noleak_ipnames;
settings_map* noleak_settings;

void Config::update(bool printsettings)
{
    FILE* fp;
    char buf[2048];
    std::string section;
    int sectiondot = 0;
    char* ptr;
    char* ptr2;
    struct stat statbuf;

    // make sure just one thread gets through the 30 second check
    time_t lastcheckvalue = lastcheck.load(memory_order_relaxed);
    if (lastcheckvalue && currtime-lastcheckvalue < 30) return;
    if (!lastcheck.compare_exchange_strong(lastcheckvalue, currtime)) return;  
    
    if (!stat(filename, &statbuf))
    {
        if (statbuf.st_mtime == lastmtime) return;      
        lastmtime = statbuf.st_mtime;
    }
    else cout << "*** " << filename << " not found" << endl;

    if ((fp = fopen(filename, "r")))
    {
        unique_ptr<stringip_map> newnameips(new stringip_map);
        unique_ptr<ipstring_map> newipnames(new ipstring_map);
        unique_ptr<settings_map> newsetting(new settings_map);

        while (fgets(buf, sizeof buf, fp))
        {
            // section header?
            if ((ptr = strchr(buf, '[')))
            {
                ptr++;
                
                if ((ptr2 = strchr(ptr, ']')))
                {
                    // check for daemon specific settings
                    char *p, *p2;

                    if ((p = strchr(ptr2, '{')) && (p2 = strchr(p, '}')))
                    {
                        section.clear();
                        for (; p < p2; p = strpbrk(p, ",} "))
                        {
                            ++p;
                            char c;
                            if (!strncmp(daemonname.c_str(), p, daemonname.size()) && (c = p[daemonname.size()], (c == ',' || c == '}' || c == ' ')))
                            {
                                section.assign(ptr, ptr2);
                            }
                        }
                    }
                    else
                    {
                        section.assign(ptr, ptr2);
                    }

                    if (!section.compare("EOF"))
                    {
                        // update the pointers other threads will use to read data.
                        // each pointer is updated atomically, but no constraints are needed on the order of changes seen on other threads
                        // once other threads get the pointer (atomically) they can read the data structure without locking as we never update it further
                        // we are currently leaking the items from the old file (tiny amounts, only when a file is manually updated)- future consideration:  c++20's atomic_shared_ptr 
                        nameips.store(noleak_nameips = newnameips.release(), memory_order_relaxed);
                        ipnames.store(noleak_ipnames = newipnames.release(), memory_order_relaxed);
                        settings.store(noleak_settings = newsetting.release(), memory_order_relaxed);
                        break;
                    } 

                    section += ".";
                    sectiondot = section.size();
                    for (auto& c : section) c = tolower(c);
                }
            }
            else
            {
                if ((ptr = skipspace(buf)))
                {
                    if (*ptr && *ptr != '#' && section[0] != '.')
                    {
                        ptr2 = findspace(ptr);
                    
                        section.replace(section.begin() + sectiondot, section.end(), ptr, ptr2++);
                        
                        if ((ptr = skipspace(ptr2)))
                        {
                            if (!section.compare(0, sectiondot, "setting.") || !section.compare(0, sectiondot, "netconfig."))
                            {
                                for (auto& c : section) c = tolower(c);
                                *findlastspace(ptr) = 0;
                                string key = section.substr(sectiondot);
                                if (newsetting->find(key) != newsetting->end())
                                {
                                    cout << "WARNING: " << section << " has multiple values, ignoring this one: " << ptr << endl;
                                }
                                else
                                {
                                    (*newsetting)[key] = ptr;
                                    if (printsettings)
                                    {
                                        cout << "local setting: " << section.substr(sectiondot) << ": '" << ptr << "'" << endl;
                                    }
                                }
                            }
                            else
                            {
                                if ((ptr2 = findspace(ptr)))
                                {
                                    *ptr2 = 0;
                                    stringip_map::iterator it = newnameips->insert(pair<string, IPv6*>(section, new IPv6(ptr)));
                                    newipnames->insert(pair<IPv6, string>(*it->second, section));
                                    //cout << "ip: " << section << " " << string(ptr) << endl;
                                }
                            }
                        }
                    }
                }
            }
        }

        fclose(fp);
    }
}

int Config::ipsbyprefix(const unsigned char* prefix, int bits, in6_addr* addrs, int maxaddrs)
{
    int prefixlen = bits >> 3;
    int mask = 255 << (8-(bits & 3));

    update();

    int i = 0;
    const ipstring_map* safe_ipnames = ipnames.load(memory_order_relaxed);  // get the pointer atomically; the data it points to never changes. 
    for (auto it = safe_ipnames->begin(); // FIXME: use lower_bound() and exit at end of range instead of performing a full scan 
            i < maxaddrs && it != safe_ipnames->end();
            it++)
    { 
        if (!memcmp(prefix, it->first.ip.s6_addr, prefixlen) && (!mask || (prefix[prefixlen] & mask) == (it->first.ip.s6_addr[prefixlen] & mask))) addrs[i++] = it->first.ip;
    }

    return i;
}

int Config::getallips(const char* prefix, in6_addr* addrs, int maxaddrs)
{
    int prefixlen;

    update();

    if (strchr((char*)prefix, '.')) prefixlen = 0;
    else prefixlen = strlen(prefix);

    int i = 0;
    const stringip_map* safe_nameips = nameips.load(memory_order_relaxed);  // get the pointer atomically; the data it points to never changes. 
    for (   stringip_map::const_iterator it = safe_nameips->lower_bound(prefix); 
            i < maxaddrs && it != safe_nameips->end() && !(prefixlen ? memcmp(prefix, it->first.data(), prefixlen) : strcmp(prefix, it->first.data())); 
            it++) 
        addrs[i++] = it->second->ip;

    return i;
}

int Config::checkipname(in6_addr* addr, const char* prefix)
{
    IPv6 ipv6(addr);
    
    int prefixlen = strlen(prefix);

    ipstring_map::const_iterator it;

    update();
    
    const ipstring_map* safe_ipnames = ipnames.load(memory_order_relaxed);  // get the pointer atomically; the data it points to never changes. 
    pair<ipstring_map::const_iterator, ipstring_map::const_iterator> range = safe_ipnames->equal_range(ipv6);

    for (it = range.first; it != range.second; it++) if (!memcmp(it->second.data(), prefix, prefixlen)) return 1;

    return 0;
}

int Config::getipname(in6_addr* addr, char* buf, int len)
{
    IPv6 ipv6(addr);
    
    update();
    
    auto safe_ipnames = ipnames.load(memory_order_relaxed);  // get the pointer atomically; the data it points to never changes. 

    auto it = safe_ipnames->find(ipv6);

    if (it == safe_ipnames->end()) return 0;

    buf[it->second.copy(buf, len-1)] = 0;

    return 1;
}

string Config::getsetting_s(const std::string& key, const std::string& defaultvalue)
{
    update();
    const settings_map* safe_settings = settings.load(memory_order_relaxed);  // get the pointer atomically; the data it points to never changes.
    auto i = safe_settings->find(key);
    if (i != safe_settings->end())
        return i->second;
    else if (parent)
        return parent->getsetting_s(key, defaultvalue);
    else
        return defaultvalue;
}

size_t Config::getsetting_u(const std::string& key, size_t defaultvalue)
{
    update();
    const settings_map* safe_settings = settings.load(memory_order_relaxed);  // get the pointer atomically; the data it points to never changes.
    auto i = safe_settings->find(key);
    if (i != safe_settings->end())
        return stoul(i->second);
    else if (parent)
        return parent->getsetting_u(key, defaultvalue);
    else
        return defaultvalue;
}
