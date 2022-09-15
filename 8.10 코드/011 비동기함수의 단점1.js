setTimeout(() => {
  console.log('첫번째일')
  setTimeout(() => {
    console.log('두번째일')
    // 어떤 문제가 발생
    setTimeout(() => {
      console.log('세번째일')
    },1000)
    setTimeout(() => {
      console.log('네번째일')
      setTimeout(() => {
        console.log('다섯번째일')
      },4000)
    },2000)
  },3000)
},5000)

//비동기 함수를 동기함수로 사용하는 방법 1. 콜백

// 콜백의 단점 1) 콜백 지옥(가독성 x)
// 2) 비동기함수를 사용했음에도, 동기함수처럼 느림
// 3)그리고 저소스코드는 모두 "성공"했을떄를 기준으로함

// -> 실패했을때는 어떤 문제가 발생할지 모름

// 콜백 패턴의 단점을 보완하기위해 promise 등장

// 1. 콜백패턴 x
// 2. 성공과 실패로 나눠서 결과를 받습니다