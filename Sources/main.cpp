#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
#include <stdexcept>
#include "person.h"



bool isEnglishName(const std::string& name) {
    unsigned int englishAlphabetRangeStart = 65;  // 영어 알파벳 대문자 유니코드 시작 범위
    unsigned int englishAlphabetRangeEnd = 90;    // 영어 알파벳 대문자 유니코드 끝 범위

    if (!name.empty() && name[0] >= englishAlphabetRangeStart && name[0] <= englishAlphabetRangeEnd) {
        return true;
    }
    else {
        return false;
    }
}

void drawGraph(const std::vector<int>& values, const std::vector<std::string>& labels) {
    int max_value = *std::max_element(values.begin(), values.end());

    for (int i = 0; i < values.size(); i++) {
        std::cout << labels[i] << " │";
        int bar_length = values[i] * 50 / max_value; // 막대의 길이를 조정하기 위해 비율 계산

        for (int j = 0; j < bar_length; j++) {
            std::cout << "█";
        }
        std::cout << '\n';
    }

    std::cout << "────┴";
    for (int i = 0; i < 50; i++) {
        std::cout << "─";
    }
    std::cout << '\n';

    std::cout << "    ";
    for (int i = 0; i < values.size(); i++) {
        std::cout << i + 1 << " ";
    }
    std::cout << '\n';
}

std::map<std::string, int> countPeopleByLanguage(const std::string& filePath) {
    // 초기화
    int koreanCount = 0;
    int chineseCount = 0;
    int englishCount = 0;

    // 파일 열기
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다.");
    }

    // 각 줄 읽기
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        // Person 구조체 생성
        Person person;
        person.name = line;

        // 언어 분석
        if (std::regex_match(std::string(1, person.name.front()), std::regex("[가-힣]"))) {
            person.language = "한국인";
            koreanCount++;
        }
        else if (std::regex_match(std::string(1, person.name.front()), std::regex("[\\x4e00-\\x9fa5]"))) {
            person.language = "중국인 + 일본인";
            chineseCount++;
        }
        else {
            person.language = "미국인";
            englishCount++;
        }
    }

    // 결과 반환
    std::map<std::string, int> result;
    result["한국인"] = koreanCount;
    result["중국인 + 일본인"] = chineseCount;
    result["미국인"] = englishCount;

    return result;
}

int main() {
    // 텍스트 파일 경로
    std::string filePath = "옵치.txt";

    try {
        // 결과 계산
        std::map<std::string, int> result = countPeopleByLanguage(filePath);

        // 결과 출력
        for (const auto& pair : result) {
            std::cout << pair.first << ": " << pair.second << "명" << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "에러 발생: " << e.what() << std::endl;
    }

    std::vector<std::string> labels = { "미국인       ", "중국인+일본인", "한국인       " };
    std::vector<int> values = { 132, 8348, 2894 };

    drawGraph(values, labels);

    return 0;
}
