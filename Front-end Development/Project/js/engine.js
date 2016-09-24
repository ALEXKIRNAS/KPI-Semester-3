require(
  {
	// Задаємо місце де буде відбуватися пошук бібліотек
    baseUrl: './',
    packages: [{
      name: 'physicsjs',
      location: 'js/physicsjs',
      main: 'physicsjs.min'
    }]
  },
  [
  'require',
  'physicsjs',
  
  // Додаткові модулі
  'js/player',
  'js/player-behavior',
  
  // Основні модулі бібліотеки
  'physicsjs/renderers/canvas',
  'physicsjs/bodies/circle',
  'physicsjs/bodies/convex-polygon',
  'physicsjs/behaviors/newtonian',
  'physicsjs/behaviors/sweep-prune',
  'physicsjs/behaviors/body-collision-detection',
  'physicsjs/behaviors/body-impulse-response'
  
], function(
  require,
  Physics
){
 // Добавляєм класи, для відображення повідомлень
	
  document.body.className = 'before-game'; // Добавляю клас для позначення стану перед грою
  
  var par = window;
  var inGame = false;
  
  // Добаляємо прослуховування нажати клавіш
  document.addEventListener('keydown', function( e ){
    
    if (!inGame && e.keyCode === 32){ // 32 - Код пробілу
      document.body.className = 'in-game';
      inGame = true;
      newGame(); // Запуск гри
    }
  });
  
  
  // Налаштовую Canvas для відмалювання вікна
  var renderer = Physics.renderer('canvas', {
    el: 'viewport',
	
	// Задаю висоту і ширину відмалювання рівною ширині і висоті вікна
    width: par.innerWidth, 
    height: par.innerHeight,
    
	
	// Задаєм стилі обєктів
    styles: {
      'circle': { // Для кола
        strokeStyle: 'rgb(0, 30, 0)',
        lineWidth: 1,
        fillStyle: 'rgb(100, 200, 50)',
        angleIndicator: false
      },
      'convex-polygon' : { // Для опуклого багатокутника
        strokeStyle: 'rgb(60, 0, 0)',
        lineWidth: 1,
        fillStyle: 'rgb(60, 16, 11)',
        angleIndicator: false
      }
    }
  });
  
  // Добавляємо реакцію на зміну розміру вікна браузера
  window.addEventListener('resize', function(){
    renderer.el.width = par.innerWidth;
    renderer.el.height = par.innerHeight;
  });
  
  // Ядро гри
  
  // Ініціалізація гри
  var init = function init( world, Physics ){
	  
	renderer.el.width = par.innerWidth;
    renderer.el.height = par.innerHeight;
  
  // Добавлення космічного корабля
   var ship = Physics.body('player', {
      x: 140,
      y: 100,
      vx: 0.08,
      radius: 30
    });
	
	var playerBehavior = Physics.behavior('player-behavior', { player: ship }); // Добавляємо поведінку гравця
    
	// Опис планети як кола
    var planet = Physics.body('circle', {
      mass: 10000,
      radius: 140,
      x: 400,
      y: 400,
    });
	
	// Cтворюємо елемент картинка і зберігаємо в властивості view
	planet.view = new Image();
    planet.view.src = require.toUrl('./img/planet.png');
    
    // Рендер на кожній ітерації
    world.on('step', function(){
	  
	  // Середина вікна
	  var middle = { 
        x: 0.5 * window.innerWidth, 
        y: 0.5 * window.innerHeight
		};
		
		// Відслідковуємо дії гравця
		renderer.options.offset.clone( middle ).vsub( ship.state.pos );
		world.render();
    });
    
    // Добавляємо обєкти
    world.add([
      ship,
	  playerBehavior,
      planet,
      Physics.behavior('newtonian', { strength: 1e-4 }), // Ньотонова гравітація (закон обернених квадратів)
      Physics.behavior('sweep-prune'), // алгоритм зіткнень обєктів
      Physics.behavior('body-collision-detection'), // алгоритм зіткнень обєктів
      Physics.behavior('body-impulse-response'), // виконання дій при зітнені обєктів
      renderer
    ]);
  };
  
  // Реініціалізація сеансу гри
  var world = null;
  var newGame = function newGame(){
    
	// Знищення минулого сеансу гри
    if (world){
      world.destroy();
    }
    
	// Ініціалізація гри
    world = Physics( init );
	
	// Реакція гри на програш гравця
    world.on('lose-game', function(){
      document.body.className = 'lose-game';
      inGame = false;
    });
	
	// Реакція гри на виграш гравця
    world.on('win-game', function(){
      world.pause();
      document.body.className = 'win-game';
      inGame = false;
    });
  };
  
  // Викликаємо функцію рендеру світу для кожного кадру
  Physics.util.ticker.on(function( time ){
    if (world){
      world.step( time ); 
    }
  }).start();
});