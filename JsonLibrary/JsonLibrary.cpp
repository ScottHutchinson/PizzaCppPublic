#include "stdafx.h"
#include "JsonLibrary.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Net;
using namespace Newtonsoft::Json;
using namespace Newtonsoft::Json::Linq;

// This function converts a managed System::String to an unmanaged std::string.
std::string toStd(System::String^ systemStr) {
    return msclr::interop::marshal_as<std::string>(systemStr);
}

ref class PizzaManaged {
public:
    List<String^>^ toppings;
};

std::vector<Pizza> GetPizzas() {
    std::vector<Pizza> ret;
    constexpr auto url = "https://scotthutchinson.github.io/assets/pizzas.json";
    auto json = String::Empty;
    try {
        ServicePointManager::Expect100Continue = true;
        ServicePointManager::SecurityProtocol = SecurityProtocolType::Tls12;
        //ServicePointManager::ServerCertificateValidationCallback = Delegate{ return true; }; // delegate syntax?
        auto Url = gcnew String(url);
        auto wc = gcnew WebClient();
        json = wc->DownloadString(Url);
        // Deserialize the json string into a managed List.
        List<PizzaManaged^>^ pizzas = JsonConvert::DeserializeObject<List<PizzaManaged^>^>(json);
        // Now copy the managed List to a native std::vector, so it can be processed in a native C++ project (pizzaCPP).
        for each(auto pizza in pizzas) {
            Pizza p{};
			for each(auto topping in pizza->toppings) {
                p.m_st.toppings.emplace_back(toStd(topping));
			}
            ret.push_back(p);
		}
    }
    catch (Exception^ ex) {
        auto exInfo = ex->ToString();
    }
    return ret;
}
