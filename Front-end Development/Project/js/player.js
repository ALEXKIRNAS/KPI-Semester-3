define(
[
    'require',
    'physicsjs',
    'physicsjs/bodies/circle',
    'physicsjs/bodies/convex-polygon'
],
function(
    require,
    Physics
){
	// Описуємо гравця розшируючи клас кола
    Physics.body('player', 'circle', function( parent ){
		
		// Привязка зображеннь корабля
		var shipImg = new Image();
		var shipThrustImg = new Image();
		shipImg.src = require.toUrl('img/ship.png');
		shipThrustImg.src = require.toUrl('img/ship.png'); //TODO
		
		// Незнаю, що тут відбувається, просто СopyPaste з форума
		
		var Pi2 = 2 * Math.PI; // 2Pi
		var deg = Math.PI/180;  // 1 градус
		
		// Округлення випадкового числа по Гауссу
		var gauss = function gauss( mean, stddev ){
				var r = 2 * (Math.random() + Math.random() + Math.random()) - 3;
				return r * stddev + mean;
		};
		
		// Функція, яка створює випадковий випуклий багатокутник
		var rndPolygon = function rndPolygon( size, n, jitter ){
				var points = [{ x: 0, y: 0 }]
					,ang = 0
					,invN = 1 / n
					,mean = Pi2 * invN
					,stddev = jitter * (invN - 1/(n+1)) * Pi2
					,i = 1
					,last = points[ 0 ]
					;
				while ( i < n ){
					ang += gauss( mean, stddev );
					points.push({
						x: size * Math.cos( ang ) + last.x,
						y: size * Math.sin( ang ) + last.y
					});
					last = points[ i++ ];
				}
				return points;
		};
		
		// Розшируємо клас кола
		return {
			
			// Змінюємо параметри кола після його створення
			init: function( options ){
				parent.init.call( this, options );
				this.view = shipImg; // присвоємо картинку для візуалізації
			},
			
			// Поворот корабля шляхом зміни його кутової швидкості
			turn: function( amount ){
				this.state.angular.vel = 0.2 * amount * deg; // установка кутової швидкості
				return this;
			},
			
			// Змінна швидкості корабля в напрямку носової частини
			thrust: function( amount ){
				var self = this;
				var world = this._world;
				if (!world){
					return self;
				}
				
				var angle = this.state.angular.pos;
				var scratch = Physics.scratchpad();
				
				amount *= 0.1; // Зменшуємо швидкість пресування
				
				// вкразую швидкість прискорення в напрямку носової частини
				var v = scratch.vector().set(
					amount * Math.cos( angle ), 
					amount * Math.sin( angle ) 
				);
				
				// самоприскорення
				this.accelerate( v );
				scratch.done();
				
				// Змінна картинки при русі корабля
				if ( amount ){
					this.view = shipThrustImg;
				} else {
					this.view = shipImg;
				}
				return self;
			},
			
			// Створюю снаряд, який вилітає з передньої частини корабля і зникає через певний проміжуток часу
			shoot: function(){
				var self = this;
				var world = this._world;
				if (!world){
					return self;
				}
				
				var angle = this.state.angular.pos;
				var cos = Math.cos( angle );
				var sin = Math.sin( angle );
				var r = this.geometry.radius + 5;
				
				// Створюю маленьке коло у носової частини корабля
				// який рухається з присконення 0.5 відностно 
				// поточної швидкості корабля по напрямяку носової частини
				var laser = Physics.body('circle', {
					x: this.state.pos.get(0) + r * cos,
					y: this.state.pos.get(1) + r * sin,
					vx: (0.5 + this.state.vel.get(0)) * cos,
					vy: (0.5 + this.state.vel.get(1)) * sin,
					radius: 2
				});
				
				// Встановлюємо властивості для імітації зіткнення
				laser.gameType = 'laser';
				
				// Робимо вистріли через кожні 600 мс
				setTimeout(function(){
					world.removeBody( laser );
					laser = undefined;
					}, 600);
					
				world.add( laser );
				return self;
				},
				
				
				// Імітація вибуху корабля при зіткнені
				blowUp: function(){
					var self = this;
					var world = this._world;
					if (!world){
						return self;
					}
					
					var scratch = Physics.scratchpad();
					var rnd = scratch.vector();
					var pos = this.state.pos;
					
					var n = 20; // Корабель буде розлітатися на 20 кусочків
					var r = 2 * this.geometry.radius; // Створюю коло розміром в гравця
					
					var size = 8 * r / n; // Розмір кусочків
					var mass = this.mass / n; // маса кусочків
					var verts; // багатокутник
					var d; // Поточний шиаточок
					var debris = []; // Масив шматочків

					// Створюю кусочки
					while ( n-- ){
						verts = rndPolygon( size, 3, 1.5 ); // створюю випадковий багатокуник
						
						if ( Physics.geometry.isPolygonConvex( verts ) ){
							
							// Вставляюю кусочок в випадкове місце відносно гравця
							rnd.set( Math.random() - 0.5, Math.random() - 0.5 ).mult( r );
							d = Physics.body('convex-polygon', {
								x: pos.get(0) + rnd.get(0),
								y: pos.get(1) + rnd.get(1),
								
								// Швидкість кусочків ріна швидкості граця
								vx: this.state.vel.get(0),
								vy: this.state.vel.get(1),
								
								// Установка випадкової кутової швидкості кусочкам
								angularVelocity: (Math.random()-0.5) * 0.06,
								mass: mass,
								vertices: verts,
								restitution: 0.8
							});
							d.gameType = 'debris';
							debris.push( d );
						}
					}

					// добавляю кусочки в світ
					world.add( debris );
					// і видаляю корабель
					world.removeBody( this );
					scratch.done();
					return self;
			}	
		};
		});

});