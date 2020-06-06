#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the JSONLIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// JSONLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef JSONLIBRARY_EXPORTS
#define JSONLIBRARY_API __declspec(dllexport)
#else
#define JSONLIBRARY_API __declspec(dllimport)
#endif

struct JSONLIBRARY_API Pizza {
    struct stToppings {
	    std::vector<std::string> toppings;
    } m_st;

    virtual ~Pizza() = default;
};

JSONLIBRARY_API std::vector<Pizza> GetPizzas();
