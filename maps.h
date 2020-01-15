#ifndef MAPS_H
#define MAPS_H

namespace maps {

static std::map<QString, int> units =
{
    {"eins", 1},
    {"zwei", 2},
    {"drei", 3},
    {"vier", 4},
    {"funf", 5},
    {"sechs", 6},
    {"sieben", 7},
    {"acht", 8},
    {"neun", 9}
};

static std::map<QString, int> tens =
{
    {"zehn", 10},
    {"zwanzig", 20},
    {"dreizig", 30},
    {"vierzig", 40},
    {"funfzig", 50},
    {"sechzig", 60},
    {"siebzig", 70},
    {"achtzig", 80},
    {"neunzig", 90},
    {"hundert", 100}
};

static std::map<QString, int> tens_plus =
{
    {"elf", 11},
    {"zwolf", 12},
    {"dreizehn", 13},
    {"vierzehn", 14},
    {"funfzehn", 15},
    {"sechzehn", 16},
    {"siebzehn", 17},
    {"achtzehn", 18},
    {"neunzehn", 19}
};

static std::map<int, QString> slava =
{
    {1, "А"},
    {2, "В"},
    {3, "Г"},
    {4, "Д"},
    {5, "Е"},
    {6, "S"},
    {7, "З"},
    {8, "И"},
    {9, "Ɵ"},
    {10, "I"},
    {20, "К"},
    {30, "Л"},
    {40, "М"},
    {50, "Н"},
    {60, "ƺ"},
    {70, "О"},
    {80, "П"},
    {90, "Ч"},
    {100, "Р"},
    {200, "С"},
    {300, "Т"},
    {400, "У"},
    {500, "Ф"},
    {600, "Х"},
    {700, "ψ"},
    {800, "ω"},
    {900, "Ц"}
};

}

#endif // MAPS_H
