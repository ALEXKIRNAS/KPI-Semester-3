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
  'js/asteroid',
  
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
  
   var par = parent;
   
   try {
      par && par.innerWidth;
   } catch( e ){
      par = window;
   }
	
  var inGame = false;
  
  // Добаляємо прослуховування нажати клавіш
  document.addEventListener('keydown', function( e ){
    
    if (!inGame && e.keyCode === 13){ // 13 - Код Enter-у
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
        strokeStyle: 'rgb(50, 50, 50)',
        lineWidth: 1,
        fillStyle: 'rgb(50, 50, 50)',
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
	  
	//renderer.el.width = par.innerWidth;
    //renderer.el.height = par.innerHeight;
  
  // Добавлення космічного корабля
   var ship = Physics.body('player', {
      x: 400,
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
      y: 300,
    });
	
	// Cтворюємо елемент картинка і зберігаємо в властивості view
	planet.view = new Image();
    planet.view.src = require.toUrl('./img/planet.png');
    
    // Рендер на кожній ітерації
    world.subscribe('step', function(){
		
		// Середина вікна
		var middle = { 
			x: 0.5 * window.innerWidth, 
			y: 0.5 * window.innerHeight
		};
		
		// Відслідковуємо гравця
		renderer.options.offset.clone( middle ).vsub( ship.state.pos );
		world.render();
    });
	
	// Стоврюю астероїди
	var asteroids = [];
	for ( var i = 0, l = 15; i < l; ++i ){

		var ang = 4 * (Math.random() - 0.5) * Math.PI;
		var r = 700 + 100 * Math.random() + i * 10;

		asteroids.push( Physics.body('asteroid', {
			x: 400 + Math.cos( ang ) * r,
			y: 300 + Math.sin( ang ) * r,
			vx: 0.03 * Math.sin( ang ),
			vy: - 0.03 * Math.cos( ang ),
			angularVelocity: (Math.random() - 0.5) * 0.001,
			radius: 50,
			mass: 30,
			restitution: 0.6}));
	}
    
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
	
	world.add(asteroids);
	
	var score = 0;
	world.subscribe('blow-up', function( data ){
		score++;
		
		var html = 'SCORE: <b>' + score + '</b>';
		document.getElementById("score").innerHTML = html;
		
		var ang = 4 * (Math.random() - 0.5) * Math.PI;
		var r = 700 + 100 * Math.random() + i * 10;

		world.add( Physics.body('asteroid', {
			x: 400 + Math.cos( ang ) * r,
			y: 300 + Math.sin( ang ) * r,
			vx: 0.03 * Math.sin( ang ),
			vy: - 0.03 * Math.cos( ang ),
			angularVelocity: (Math.random() - 0.5) * 0.001,
			radius: 50,
			mass: 30,
			restitution: 0.6}));
	});

	// Знищуєм астероїди
	world.subscribe('collisions:detected', function( data ){
		var collisions = data.collisions
			,col
			;

		for ( var i = 0, l = collisions.length; i < l; ++i ){
			col = collisions[ i ];

			if (col.bodyA.gameType === 'laser' || col.bodyB.gameType === 'laser'){
				if ( col.bodyA.blowUp ){
					col.bodyA.blowUp();
					world.removeBody(col.bodyB);
					
					col.bodyB = undefined;
				} else if ( col.bodyB.blowUp ){
					col.bodyB.blowUp();
					world.removeBody(col.bodyA);
					col.bodyA = undefined;
				}
				else if(col.bodyA.gameType === 'laser') {
					world.removeBody(col.bodyA);
					col.bodyA = undefined;
				}
				else if(col.bodyB.gameType === 'laser'){
					world.removeBody(col.bodyB);
					col.bodyB = undefined;
				}
				return;
			}
		}
	});

	// Малюємо мінікарту
	world.subscribe('render', function( data ){
		// Радіус мінікарти
		var r = 100;
		
		// Відступи
		var shim = 15;
		
		// Координати x,y центра
		var x = renderer.options.width - r - shim;
		var y = r + shim;
		
		var scratch = Physics.scratchpad();
		var d = scratch.vector();
		var lightness;
		
		// Малюємо круги на радарі
		renderer.drawCircle(x, y, r, { strokeStyle: '#090', fillStyle: '#010' });
		renderer.drawCircle(x, y, r * 2 / 3, { strokeStyle: '#090' });
		renderer.drawCircle(x, y, r / 3, { strokeStyle: '#090' });
		
		for (var i = 0, l = data.bodies.length, b = data.bodies[ i ]; b = data.bodies[ i ]; i++){
			
			// Розраховую зміщення тіла відносно корабля
			d.clone( ship.state.pos ).vsub( b.state.pos ).mult( -0.05 );
			
			// Обчислюють колір в залежності від маси
			lightness = Math.max(Math.min(Math.sqrt(b.mass*10)|0, 100), 10);
			
			// Малюю точку
			if(b.mass >= 0.001)   renderer.drawCircle(x + d.get(0), y + d.get(1), 1, 'hsl(60, 100%, '+lightness+'%)');
			
		}

		scratch.done();
	});
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
    world.subscribe('lose-game', function(){
      document.body.className = 'lose-game';
      inGame = false;
    });
	
	// Реакція гри на виграш гравця
    world.subscribe('win-game', function(){
      world.pause();
      document.body.className = 'win-game';
      inGame = false;
    });
  };
  
  // Викликаємо функцію рендеру світу для кожного кадру
  Physics.util.ticker.subscribe(function( time ){
    if (world){
      world.step( time ); 
    }
  }).start();
});