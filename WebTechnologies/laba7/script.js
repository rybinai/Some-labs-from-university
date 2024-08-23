const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const end = document.getElementById('endscreen');
const win = document.getElementById('winscreen');
const restartButton = document.getElementById('restartButton');
const restartButtonn = document.getElementById('restartButtonn');
let gameStarted = false;
let isGameOver = false;

// Начало игры = пробел
document.addEventListener("keydown", function(event) {
  if (event.code === "Space") {
    if (!gameStarted) {
      gameStarted = true;
      elementsVisibleBeforeStart = true;
      gameLoop();
    }
  }
});

// Начальные параметры платформы
let platformX = canvas.width / 2 - 60;
const platformWidth = 120;
const platformHeight = 10;
const platformSpeed = 8;

// Начальные параметры мяча
let ballX = canvas.width / 2;
let ballY = canvas.height - 30;
let ballSpeedX = 2;
let ballSpeedY = -2;
const ballRadius = 10;

// Параметры блоков
const blockRowCount = 5;
const blockColumnCount = 5;
const blockWidth = 75;
const blockHeight = 20;
const blockPadding = 10;
const blockOffsetTop = 30;
const blockOffsetLeft = 30;

// Создаем массив блоков
const blocks = [];
for (let c = 0; c < blockColumnCount; c++) {
  blocks[c] = [];
  for (let r = 0; r < blockRowCount; r++) {
    blocks[c][r] = { x: 0, y: 0, status: 1 };
  }
}

// Обработка нажатий клавиш
document.addEventListener('keydown', keyDownHandler, false);
document.addEventListener('keyup', keyUpHandler, false);

let rightPressed = false;
let leftPressed = false;

function keyDownHandler(e) {
  if (e.key === 'Right' || e.key === 'ArrowRight') {
    rightPressed = true;
  } else if (e.key === 'Left' || e.key === 'ArrowLeft') {
    leftPressed = true;
  }
}

function keyUpHandler(e) {
  if (e.key === 'Right' || e.key === 'ArrowRight') {
    rightPressed = false;
  } else if (e.key === 'Left' || e.key === 'ArrowLeft') {
    leftPressed = false;
  }
}

// Отрисовка платформы
function drawPlatform() {
  ctx.beginPath();
  ctx.rect(platformX, canvas.height - platformHeight, platformWidth, platformHeight);
  ctx.fillStyle = '#0095DD';
  ctx.fill();
  ctx.closePath();
}

// Отрисовка мяча
function drawBall() {
  ctx.beginPath();
  ctx.arc(ballX, ballY, ballRadius, 0, Math.PI * 2);
  ctx.fillStyle = '#0095DD';
  ctx.fill();
  ctx.closePath();
}

// You Win
function checkGameStatus() {
  let count = 0;
  for (let c = 0; c < blockColumnCount; c++) {
    for (let r = 0; r < blockRowCount; r++) {
      if (blocks[c][r].status === 1) {
        count++;
      }
    }
  }

  if (count === 0) {
    ballSpeedX = 0; 
    ballSpeedY = 0;
    win.style.display = 'block'; 
    restartButtonn.onclick = function() {
    document.location.reload();
    }
  }
}

// Отрисовка блоков
function drawBlocks() {
  for (let c = 0; c < blockColumnCount; c++) {
    for (let r = 0; r < blockRowCount; r++) {
      if (blocks[c][r].status === 1) {
        const blockX = (c * (blockWidth + blockPadding)) + blockOffsetLeft;
        const blockY = (r * (blockHeight + blockPadding)) + blockOffsetTop;
        blocks[c][r].x = blockX;
        blocks[c][r].y = blockY;
        ctx.beginPath();
        ctx.rect(blockX, blockY, blockWidth, blockHeight);
        ctx.fillStyle = '#0095DD';
        ctx.fill();
        ctx.closePath();
      }
    }
  }
}

// Обработка столкновений мяча с блоками
function collisionDetection() {
  for (let c = 0; c < blockColumnCount; c++) {
    for (let r = 0; r < blockRowCount; r++) {
      const block = blocks[c][r];
      if (block.status === 1) {
        if (ballX > block.x && ballX < block.x + blockWidth 
          && ballY > block.y && ballY < block.y + (blockHeight+10)) {
          ballSpeedY = -ballSpeedY;
          block.status = 0; // разрушен
        }
      }
    }
  }
  checkGameStatus();
}

// Отрисовка элементов до начала игры
drawBlocks();
drawPlatform();
drawBall();
collisionDetection();

// Главный игровой цикл
function gameLoop() {
  if (!gameStarted){
    // Очищаем поле 
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // Отрисовка элементов
    drawBlocks();
    drawPlatform();
    drawBall();
    collisionDetection();
  }
  if (gameStarted) {
    ctx.clearRect(0, 0, canvas.width, canvas.height); // Очищаем поле

    // Уход левой и правой границы
    if (ballX + ballSpeedX > canvas.width - ballRadius || ballX + ballSpeedX < ballRadius) {
      ballSpeedX = -ballSpeedX;
    }
    // Уход верхней границы
    if (ballY + ballSpeedY < ballRadius) {
      ballSpeedY = -ballSpeedY; 
      ballY = ballRadius;
    }
    // Уход вниз и смерть
    if (ballY + ballSpeedY > canvas.height - ballRadius) {
      if (!isGameOver) {
        isGameOver = true; 
        ballSpeedX = 0; 
        ballSpeedY = 0; 
        // Окно Restart 
        end.style.display = 'block';
        restartButton.onclick = function() {
        document.location.reload();
        }
      }
    }

    // Проверка платформы 
    if (ballY + ballSpeedY > canvas.height - ballRadius - platformHeight) {
      if (ballX > platformX && ballX < platformX + platformWidth) {
        ballSpeedY = -ballSpeedY;
      }
    }

    // Движение платформы по нажатию клавиш
    if (rightPressed && platformX < canvas.width - platformWidth) {
      platformX += platformSpeed;
    } else if (leftPressed && platformX > 0) {
      platformX -= platformSpeed;
    }

    // Ограничения шарика в пределах поля
    if (ballX + ballSpeedX > canvas.width - ballRadius || ballX + ballSpeedX < ballRadius) {
      ballSpeedX = -ballSpeedX;
    }

    // Двигаем мяч
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Отрисовка элементов
    drawBlocks();
    drawPlatform();
    drawBall();
    collisionDetection();

    requestAnimationFrame(gameLoop); 
  }
  else {
    requestAnimationFrame(gameLoop);
  }
}