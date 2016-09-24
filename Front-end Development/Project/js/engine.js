require(
  {
	// ������ ���� �� ���� ���������� ����� �������
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
  
  // �������� �����
  'js/player',
  'js/player-behavior',
  'js/asteroid',
  
  // ������ ����� ��������
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
 // ��������� �����, ��� ����������� ����������
	
  document.body.className = 'before-game'; // �������� ���� ��� ���������� ����� ����� ����
  
   var par = parent;
   
   try {
      par && par.innerWidth;
   } catch( e ){
      par = window;
   }
	
  var inGame = false;
  
  // ��������� ��������������� ������ �����
  document.addEventListener('keydown', function( e ){
    
    if (!inGame && e.keyCode === 32){ // 32 - ��� ������
      document.body.className = 'in-game';
      inGame = true;
      newGame(); // ������ ���
    }
  });
  
  
  // ���������� Canvas ��� ����������� ����
  var renderer = Physics.renderer('canvas', {
    el: 'viewport',
	
	// ����� ������ � ������ ����������� ����� ����� � ����� ����
    width: par.innerWidth, 
    height: par.innerHeight,
    
	
	// ����� ���� �����
    styles: {
      'circle': { // ��� ����
        strokeStyle: 'rgb(0, 30, 0)',
        lineWidth: 1,
        fillStyle: 'rgb(100, 200, 50)',
        angleIndicator: false
      },
      'convex-polygon' : { // ��� �������� �������������
        strokeStyle: 'rgb(60, 0, 0)',
        lineWidth: 1,
        fillStyle: 'rgb(60, 16, 11)',
        angleIndicator: false
      }
    }
  });
  
  // ���������� ������� �� ���� ������ ���� ��������
  window.addEventListener('resize', function(){
    renderer.el.width = par.innerWidth;
    renderer.el.height = par.innerHeight;
  });
  
  // ���� ���
  
  // ����������� ���
  var init = function init( world, Physics ){
	  
	//renderer.el.width = par.innerWidth;
    //renderer.el.height = par.innerHeight;
  
  // ���������� ��������� �������
   var ship = Physics.body('player', {
      x: 400,
      y: 100,
      vx: 0.08,
      radius: 30
    });
	
	var playerBehavior = Physics.behavior('player-behavior', { player: ship }); // ���������� �������� ������
    
	// ���� ������� �� ����
    var planet = Physics.body('circle', {
      mass: 10000,
      radius: 140,
      x: 400,
      y: 300,
    });
	
	// C�������� ������� �������� � �������� � ���������� view
	planet.view = new Image();
    planet.view.src = require.toUrl('./img/planet.png');
    
    // ������ �� ����� ��������
    world.subscribe('step', function(){
		
		// �������� ����
		var middle = { 
			x: 0.5 * window.innerWidth, 
			y: 0.5 * window.innerHeight
		};
		
		// ³���������� ������
		renderer.options.offset.clone( middle ).vsub( ship.state.pos );
		world.render();
    });
	
	// ������� ��������
	var asteroids = [];
	for ( var i = 0, l = 30; i < l; ++i ){

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
    
    // ���������� �����
    world.add([
      ship,
	  playerBehavior,
      planet,
      Physics.behavior('newtonian', { strength: 1e-4 }), // ��������� ��������� (����� ��������� ��������)
      Physics.behavior('sweep-prune'), // �������� ������� �����
      Physics.behavior('body-collision-detection'), // �������� ������� �����
      Physics.behavior('body-impulse-response'), // ��������� �� ��� ����� �����
      renderer
    ]);
	
	world.add(asteroids);
	
	var score = 0;
	world.subscribe('blow-up', function( data ){
		score++;
		
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

	// ������ ��������
	world.subscribe('collisions:detected', function( data ){
		var collisions = data.collisions
			,col
			;

		for ( var i = 0, l = collisions.length; i < l; ++i ){
			col = collisions[ i ];

			if (col.bodyA.gameType === 'laser' || col.bodyB.gameType === 'laser'){
				if ( col.bodyA.blowUp ){
					col.bodyA.blowUp();
				} else if ( col.bodyB.blowUp ){
					col.bodyB.blowUp();
				}
				return;
			}
		}
	});
  };
  
  // ������������ ������ ���
  var world = null;
  var newGame = function newGame(){
    
	// �������� �������� ������ ���
    if (world){
      world.destroy();
    }
    
	// ����������� ���
    world = Physics( init );
	
	// ������� ��� �� ������� ������
    world.subscribe('lose-game', function(){
      document.body.className = 'lose-game';
      inGame = false;
    });
	
	// ������� ��� �� ������ ������
    world.subscribe('win-game', function(){
      world.pause();
      document.body.className = 'win-game';
      inGame = false;
    });
  };
  
  // ��������� ������� ������� ���� ��� ������� �����
  Physics.util.ticker.subscribe(function( time ){
    if (world){
      world.step( time ); 
    }
  }).start();
});