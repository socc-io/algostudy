###알고스터디용  "소스 자동생성 & 소스 자동빌드 & 자동 인풋 입력 " 도구

현재 지원하는 OS는 Mac, Linux, Window(CPP)

현재 지원하는 언어는 Cpp 뿐입니다. 종종 추가하겠습니다.

우선 문제를 풀려는 디렉토리에 algoWatch.sh, genWinCpp.py, genCpp.py, pydemon.py 를 복사합니다.

----------------

#####1. SAMPLE 이라는 문제를 풀고싶다면, 아래와 같은 명령어를 입력하세요.
$./algoWatch.sh SAMPLE cpp

    SAMPLE.cpp SAMPLE.input generated
    run [g++ SAMPLE.cpp -o SAMPLE.o;./SAMPLE.o SAMPLE.input ]
    [stderr]----------------------
    [stdout]----------------------
    hello-algostudy!
    pydemon watching your directory...

#####윈도우 cpp는 아래처럼 생성해주세요

$./algoWatch.sh SAMPLE wincpp

-----------------

#####2. 소스 자동생성만 하고 싶다면, 아래와 같은 명령어를 입력하세요 (현재 CPP만)
$./genCpp.py SAMPLE

    SAMPLE.cpp SAMPLE.input generated

-----------------

#####3. 자동 빌드만 하고 싶다면, 아래와 같이 ./pydemon 다음에 "" 따옴표 사이에 bash 명령어를 입력하세요. 
$./pydemon.py "g++ SAMPLE.cpp -o SAMPLE.o;./SAMPLE.o SAMPLE.input"

혹은,

$./pydemon.py script.sh

    run [g++ SAMPLE.cpp -o SAMPLE.o;./SAMPLE.o SAMPLE.input ]
    [stderr]-----------------------
    [stdout]----------------------
    hello-algostudy!
    pydemon watching your directory...

