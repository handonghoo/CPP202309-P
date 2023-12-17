#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <locale>
#include <unordered_map>

// 주어진 문자열이 한국어인지 영어인지 일본어인지 중국어인지 판별하는 함수
std::string detectLanguage(const std::string& str) {
    bool hasKorean = false;
    bool hasEnglish = false;
    bool hasJapanese = false;
    bool hasChinese = false;

    for (char c : str) {
        // 문자가 한글 범위에 속하는지 확인
        if (c >= 0xAC00 && c <= 0xD7AF) {
            hasKorean = true;
        }
        // 문자가 알파벳 범위에 속하는지 확인
        else if (std::isalpha(c, std::locale(""))) {
            hasEnglish = true;
        }
        // 문자가 일본어 범위에 속하는지 확인
        else if (c >= 0x3040 && c <= 0x30FF) {
            hasJapanese = true;
        }
        // 문자가 중국어 범위에 속하는지 확인
        else if (c >= 0x4E00 && c <= 0x9FFF) {
            hasChinese = true;
        }

        // 모든 언어가 포함되어 있는 경우 판별 종료
        if (hasKorean && hasEnglish && hasJapanese && hasChinese) {
            return "혼합된 언어";
        }
    }

    // 언어별로 포함되어 있는 경우 판별
    if (hasKorean) {
        return "한국어";
    }
    else if (hasEnglish) {
        return "영어";
    }
    else if (hasJapanese) {
        return "일본어";
    }
    else if (hasChinese) {
        return "중국어";
    }
    else {
        return "알 수 없음";
    }
}

// 언어들과 해당 언어의 이름 개수를 출력하는 함수
void printLanguageCounts(const std::unordered_map<std::string, int>& languageCounts) {
    std::cout << "언어별 이름 개수:" << std::endl;
    for (const auto& pair : languageCounts) {
        std::cout << pair.first << ": " << pair.second << "개" << std::endl;
    }
    std::cout << std::endl;
}

// 언어별 이름 개수를 그래프 도식화하여 콘솔 창에 출력하는 함수
void printGraph(const std::unordered_map<std::string, int>& languageCounts) {
    int maxCount = 0;
    for (const auto& pair : languageCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
        }
    }

    std::cout << "언어별 이름 개수 그래프:" << std::endl;
    for (const auto& pair : languageCounts) {
        std::cout << pair.first << ": ";
        int barLength = static_cast<int>(static_cast<double>(pair.second) / maxCount * 50);
        for (int i = 0; i < barLength; ++i) {
            std::cout << "#";
        }
        std::cout << " (" << pair.second << "개)" << std::endl;
    }
}

int main() {
    std::ifstream file("example.txt");
    if (!file) {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    std::unordered_map<std::string, int> languageCounts; // 언어별 이름 개수를 저장할 해시 맵

    std::string line;
    while (std::getline(file, line)) {
        std::string language = detectLanguage(line);
        languageCounts[language]++;
    }

    file.close();

    printLanguageCounts(languageCounts);
    printGraph(languageCounts);

    return 0;
}
