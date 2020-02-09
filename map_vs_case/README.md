현재 프로젝트에서 switch-case로 약1000개의 함수를 case별로 호출하는데
함수개수가 늘어나면서 관리가 쉽지 않음.
그래서 std::map으로 교체했을때 성능상에 문제가 없는지를 확인하기 위해 만듬.

환경은 Windows10 x64, VS2010

측정방법은 함수10개를 만들고 index값을 인자로 주어 해당 index에 대응하는 함수포인터를 리턴하도록 한다.
이를 switch-case, array, std::map, std::array, std::vector, if-else 로 각각 5000만회 호출했을때의 성능을 알아본다.

테스트한 결과는 아래 이미지와 같음.

결론은 map이 2배 정도 느린 것으로 나왔지만,
실제 프로그램의 동작환경을 생각했을때에는
실질적인 차이가 전혀 없기 때문에 상황에 맞는 방법을 사용하면 될 듯...

![](https://github.com/smok95/performance-test/blob/master/map_vs_case/result-2020_02_09.png?raw=true)
