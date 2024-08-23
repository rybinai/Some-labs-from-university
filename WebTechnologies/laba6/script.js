document.getElementById('form').addEventListener('submit', function(e) {
  e.preventDefault(); 
  
  fetch('answers.json')
    .then(response => response.json()) 
    .then(answers => {

      let score = 0; 

      if (document.querySelector('input[name="q1"]:checked').value === answers.question1) {
        score++;
      }

      if (document.querySelector('input[name="q2"]:checked').value === answers.question2) {
        score++;
      }

      let q3Answers = Array.from(document.querySelectorAll('input[name="q3"]:checked')).map(el => el.value);
      if (q3Answers.length === answers.question3.length && q3Answers.every(val => answers.question3.includes(val))) {
        score++;
      }

      let q4Answers = Array.from(document.querySelectorAll('input[name="q4"]:checked')).map(el => el.value);
      if (q4Answers.length === answers.question4.length && q4Answers.every(val => answers.question4.includes(val))) {
        score++;
      }

      if (parseInt(document.querySelector('input[name="q5"]').value) === answers.question5) {
        score++;
      }

      if (parseInt(document.querySelector('input[name="q6"]').value) === answers.question6) {
        score++;
      }

      if (document.querySelector('input[name="q7"]').value.toLowerCase() === answers.question7.toLowerCase()) {
        score++;
      }

      if (document.querySelector('input[name="q8"]').value.toLowerCase() === answers.question8.toLowerCase()) {
        score++;
      }

      alert('Ваш результат: ' + score + ' из 8');
    });
});
