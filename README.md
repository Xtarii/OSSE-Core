# OpenSource Search Engine

This is a simple small project for an open source search engine.

**OSSE ( OpenSource Search Engine ) Core** is a base search engine
made to integrate into any search engine.

The job of the core is to map the web and provide functions
for clients to search the internet map.



### Why

I want to learn C++ and Networking, maybe some search engine-ish as well.
So to learn more I made this search engine.

And yes, I know that there are some things that can be improved and made better.





# Installation

There are multiple ways to install the **OSSE Core** library.

**Installation on Arch Linux**
```bash
yay -S osse-core
```

**Installation from github**
```bash
git clone https://github.com/Xtarii/OSSE-Core
cd OSSE-Core

mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release
make

sudo make install
```

**Import with CMAKE to project**
```bash
find_package(OSSE)
...
target_link_libraries(<target> OSSE::osse)
```





# How to use

Examples of how to use `OSSE`

### Managers

When creating a manager ( an object that controls workers ), a database
is needed as a place where the workers can store the data.

It is **NOT RECOMMENDED** to use `simple_database` due to the
slow speed. But if one wants to use `simple_database` one can
set the managers database as follows,
```cpp
OSSE::Manager manager(tags, nullptr);
manager.setDatabase(new OSSE::simple_database());
```

The recommended way to use databases is to **override** the functions in
`abstract_database` and connect to a database of ones liking such as MongoDB,
Supabase or anything else,
```cpp
struct my_db : OSSE::abstract_database {
    /* Custom implementation */
}

...

manager.setDatabase(new my_db());
```

The functions that should be **overwritten** from `abstract_database` is as follows
- add(database_object* obj) &rarr; **void**
- remove(std::string URI) &rarr; **void**
- remove(OSSE::URI URI) &rarr; **void**
- find(OSSE::string_set tags) &rarr; **OSSE::database_result**



### Config and Robots

**OSSE** uses configuration files to customize the engine.
It is possible to use it without configuration files.
```cpp

// Instead of a configuration object, a **nullptr** is passed as parameter.

OSSE::Robots* robots = OSSE::Robots::load(&URI, nullptr);
```



If a configuration file is wanted to change any engine functions,
a file can simply be loaded into to a ```Config``` object
```cpp
std::string path = "config.osse";
OSSE::Config config = OSSE::Config::load(path);
```

The file extension is not specific and can be anything specified, however
a convenient extension is **.osse** and configuration files will be referred
to as **.osse** files.


The names for each config is the same as the code name. The default configuration
uses the variable name as the configuration name.
```const OSSE_CONFIG_TYPE AGENT {"AGENT", "*"};```
where the variable is named ```AGENT``` and when searching in configuration files
it will be referred to as ```AGENT```



### Crawlers

Crawlers take a list [ `CONFIG_LIST` ] containing tags used for analyzing websites.
There is no default `Tags.list` file or defaults for tags in the core. **Tags** must
be provided to the search engine for the analyzing to work.

There is also a need to provide a list of **default-URI**. A list of URLs used
by the search engine's crawlers when starting to provide a base of known websites.
If this list is not provided the search engines crawlers is basically on a nice spa day.
