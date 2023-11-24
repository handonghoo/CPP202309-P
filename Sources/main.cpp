#include <iostream>
#include <string>
#include <regex>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::regex;
using std::regex_search;

bool isKorean(const string& text) {
    regex koreanRegex("[ㄱ-ㅎ가-힣]+");
    return regex_search(text, koreanRegex);
}

bool isChinese(const string& text) {
    regex chineseRegex("[\u4E00-\u9FFF]+");
    return regex_search(text, chineseRegex);
}

bool isJapanese(const string& text) {
    regex japaneseRegex("[\u3040-\u30FF]+");
    return regex_search(text, japaneseRegex);
}

bool isEnglish(const string& text) {
    regex englishRegex("[A-Za-z]+");
    return regex_search(text, englishRegex);
}

int main() {
    string text;
    cout << "텍스트를 입력하세요: ";
    getline(cin, text);

    if (isKorean(text))
        cout << "입력한 텍스트는 한국어입니다." << endl;
    else if (isChinese(text))
        cout << "输入的文本是中文。" << endl;
    else if (isJapanese(text))
        cout << "入力されたテキストは日本語です。" << endl;
    else if (isEnglish(text))
        cout << "The input text is in English." << endl;
    else
        cout << "입력한 텍스트의 언어를 구별할 수 없습니다." << endl;

    return 0;
}
