#include "../headers/core.h"
#include "../headers/URI/URI.h"
#include "../headers/robots/Robots.h"
#include "../headers/HTML/HTML.h"

#include <string>



int main() {
    std::string agent = "*";
    std::string url = "https://google.com/";

    OSSE::URI URI = OSSE::URI::parse(url, nullptr);

    OSSE::Robots robots = OSSE::Robots::load(&URI, nullptr);

    std::string page = OSSE::GET(URI);
    OSSE::HTML::Document document(page);



    return 0;
}
