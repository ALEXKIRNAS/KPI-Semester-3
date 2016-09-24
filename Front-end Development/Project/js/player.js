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
	// ������� ������ ���������� ���� ����
    Physics.body('player', 'circle', function( parent ){
		
		// �������� ���������� �������
		var shipImg = new Image();
		var shipThrustImg = new Image();
		shipImg.src = require.toUrl('img/ship.png');
		shipThrustImg.src = require.toUrl('img/ship.png'); //TODO
		
		// ������, �� ��� ����������, ������ �opyPaste � ������
		
		var Pi2 = 2 * Math.PI; // 2Pi
		var deg = Math.PI/180;  // 1 ������
		
		// ���������� ����������� ����� �� ������
		var gauss = function gauss( mean, stddev ){
				var r = 2 * (Math.random() + Math.random() + Math.random()) - 3;
				return r * stddev + mean;
		};
		
		// �������, ��� ������� ���������� �������� ������������
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
		
		// ��������� ���� ����
		return {
			
			// ������� ��������� ���� ���� ���� ���������
			init: function( options ){
				parent.init.call( this, options );
				this.view = shipImg; // �������� �������� ��� ����������
			},
			
			// ������� ������� ������ ���� ���� ������ ��������
			turn: function( amount ){
				this.state.angular.vel = 0.2 * amount * deg; // ��������� ������ ��������
				return this;
			},
			
			// ����� �������� ������� � �������� ������ �������
			thrust: function( amount ){
				var self = this;
				var world = this._world;
				if (!world){
					return self;
				}
				
				var angle = this.state.angular.pos;
				var scratch = Physics.scratchpad();
				
				amount *= 0.1; // �������� �������� ����������
				
				// ������� �������� ����������� � �������� ������ �������
				var v = scratch.vector().set(
					amount * Math.cos( angle ), 
					amount * Math.sin( angle ) 
				);
				
				// ���������������
				this.accelerate( v );
				scratch.done();
				
				// ����� �������� ��� ��� �������
				if ( amount ){
					this.view = shipThrustImg;
				} else {
					this.view = shipImg;
				}
				return self;
			},
			
			// ������� ������, ���� ����� � �������� ������� ������� � ����� ����� ������ ��������� ����
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
				
				// ������� �������� ���� � ������ ������� �������
				// ���� �������� � ����������� 0.5 �������� 
				// ������� �������� ������� �� ��������� ������ �������
				var laser = Physics.body('circle', {
					x: this.state.pos.get(0) + r * cos,
					y: this.state.pos.get(1) + r * sin,
					vx: (0.5 + this.state.vel.get(0)) * cos,
					vy: (0.5 + this.state.vel.get(1)) * sin,
					radius: 2
				});
				
				// ������������ ���������� ��� ������� ��������
				laser.gameType = 'laser';
				
				// ������ ������� ����� ���� 600 ��
				setTimeout(function(){
					world.removeBody( laser );
					laser = undefined;
					}, 600);
					
				world.add( laser );
				return self;
				},
				
				
				// ������� ������ ������� ��� ������
				blowUp: function(){
					var self = this;
					var world = this._world;
					if (!world){
						return self;
					}
					
					var scratch = Physics.scratchpad();
					var rnd = scratch.vector();
					var pos = this.state.pos;
					
					var n = 20; // �������� ���� ���������� �� 20 �������
					var r = 2 * this.geometry.radius; // ������� ���� ������� � ������
					
					var size = 8 * r / n; // ����� �������
					var mass = this.mass / n; // ���� �������
					var verts; // ������������
					var d; // �������� ��������
					var debris = []; // ����� ��������

					// ������� �������
					while ( n-- ){
						verts = rndPolygon( size, 3, 1.5 ); // ������� ���������� �����������
						
						if ( Physics.geometry.isPolygonConvex( verts ) ){
							
							// ��������� ������� � ��������� ���� ������� ������
							rnd.set( Math.random() - 0.5, Math.random() - 0.5 ).mult( r );
							d = Physics.body('convex-polygon', {
								x: pos.get(0) + rnd.get(0),
								y: pos.get(1) + rnd.get(1),
								
								// �������� ������� ��� �������� �����
								vx: this.state.vel.get(0),
								vy: this.state.vel.get(1),
								
								// ��������� ��������� ������ �������� ��������
								angularVelocity: (Math.random()-0.5) * 0.06,
								mass: mass,
								vertices: verts,
								restitution: 0.8
							});
							d.gameType = 'debris';
							debris.push( d );
						}
					}

					// �������� ������� � ���
					world.add( debris );
					// � ������� ��������
					world.removeBody( this );
					scratch.done();
					return self;
			}	
		};
		});

});