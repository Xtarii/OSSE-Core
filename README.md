# OpenSource Search Engine

This is a simple small project for an open source search engine.

**OSSE ( OpenSource Search Engine ) Core** is a base search engine
made to integrate into any search engine.

The job of the core is to map the web and provide functions
for clients to search the internet map.



### Why

I want to learn C++ and Networking, maybe some search engine-ish as well.
So to learn more I made this search engine.



### How to use

**OSSE** uses configuration files to customize the engine.
It is possible to use it without configuration files.
```cpp

// Instead of a configuration object, a **nullptr** is passed as parameter.

OSSE::Robots robots = OSSE::Robots::load(&URI, nullptr);
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
