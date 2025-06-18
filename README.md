# LongplayTest

## 프로젝트 구성
Algorithm.cpp/h  ->  알고리즘 코드가 있는 파일입니다.   
WallSets.cpp     ->  Wallset을 미리 입력할 수 있는 파일입니다.   
main.cpp         ->  test를 실행하는 main이 있는 파일입니다.   

## 테스트 구성
솔루션을 실행하면 다음과 같이 터미널에 어떤 테스트를 실행할지 입력하는 창이 뜹니다.
![image](https://github.com/user-attachments/assets/413f5c03-81fb-4519-bae1-05997affc590)

해당하는 번호를 눌러 테스트를 실행할 수 있습니다.
## 1 입력 -> Preset Test 
Preset Test의 경우, WallSets.cpp에 입력된 데이터를 기반으로 하나씩 테스트를 실행합니다. 한 케이스의 실행이 끝나면 터미널에 빨간색 숫자로 경로가, 파란색 문자로 벽데이터가 뜨고, 그 밑에 경로의 좌표가 출력됩니다.마지막 줄에는 테스트에 걸린 시간이 ms단위로 출력됩니다.   

Preset SET1 출력 예시
![image](https://github.com/user-attachments/assets/30985947-8c1c-4370-aef7-9215cd1c79c3)

한 케이스 실행이 끝나고 터미널에 n을 입력하면 다음 케이스가 실행됩니다. WallSets.cpp에 적힌 데이터가 모두 실행되면 프로그램이 종료됩니다.


## 2 입력 -> Random Test
랜덤으로 생성되는 데이터를 기반으로 하나씩 테스트를 실행합니다. 출력창과 다음 케이스 실행방식은 Preset Test와 동일합니다.

## 3 입력 -> Performance Test
랜덤으로 생성되는 데이터를 기반으로 100개씩 테스트를 진행하고 걸린 평균시간을 ms단위로 출력합니다.

Performance Test 출력 예시
![image](https://github.com/user-attachments/assets/43021819-05c1-4522-896b-93c938746c03)


