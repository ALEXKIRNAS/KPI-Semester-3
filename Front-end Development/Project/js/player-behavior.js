define(
[
    'physicsjs'
],
function(
    Physics
){

    return Physics.behavior('player-behavior', function( parent ){

        return {
            init: function( options ){
                var self = this;
                parent.init.call(this, options);
                
				// ������� ������ ����� ��������� options � ������� ����
                var player = self.player = options.player;
                self.gameover = false;

               // ������� ������������� ���� � ����� �� ������ �����
                document.addEventListener('keydown', function( e ){
                    if (self.gameover){
                        return;
                    }
                    switch ( e.keyCode ){
                        case 38: // �����
                            self.movePlayer();
                        break;
						case 40: // ����
							 self.movePlayer( false );
                        break;
                        case 37: // ����
                            player.turn( -1 );
                        break;
                        case 39: // ������
                            player.turn( 1 );
                        break;
                        case 32: // �����
                            player.shoot();
                        break;
                    }
                    return false;
                });
				
				// ������� ������������� ���� � ����� �� ���������� �����
                document.addEventListener('keyup', function( e ){
                    if (self.gameover){
                        return;
                    }
                    switch ( e.keyCode ){
                        case 38: // �����
                            self.movePlayer( false );
                        break;
						case 40: // ����
							 self.movePlayer( false );
                        break;
                        case 37: // ����
                            player.turn( 0 );
                        break;
                        case 39: // ������
                            player.turn( 0 );
                        break;
                    }
                    return false;
                });
            },

            // �������, ��� ����������� �����������, ���� ����� ���������� �� ����
            connect: function( world ){
                // ³���������� ��䳿 � ���
                world.on('collisions:detected', this.checkPlayerCollision, this);
                world.on('integrate:positions', this.behave, this);
            },

            // �������, ��� ����������� �����������, ���� ����� ����������� �� ����
            disconnect: function( world ){
				// ��������� ������������� ��䳿 � ���
                world.off('collisions:detected', this.checkPlayerCollision);
                world.off('integrate:positions', this.behave);
            },

            // ������� �� �������� ������ � ����-���
            checkPlayerCollision: function( data ){

                var self = this
                    ,world = self._world
                    ,collisions = data.collisions
                    ,col
                    ,player = this.player
                    ;

                for ( var i = 0, l = collisions.length; i < l; ++i ){
                    col = collisions[ i ];

					// �������� ������� ����� � ������ � ���������� �� ����� �� �� ���糿 � �������
                    if ( col.bodyA.gameType !== 'debris' && 
                        col.bodyB.gameType !== 'debris' && 
                        (col.bodyA === player || col.bodyB === player)
                    ){
						
                        player.blowUp();
                        world.removeBehavior( this );
                        this.gameover = true;

                        // �������� ���
                        world.publish('lose-game');
                        return;
                    }
                }
            },

           // ������������ ����� ������ (�������� �� �)
            movePlayer: function( active ){

                if ( active === false ){
                    this.playerMove = false;
                    return;
                }
                this.playerMove = true;
            },

            behave: function( data ){

                // �������� ���, ���� playerMove === true
                this.player.thrust( this.playerMove === true ? 1 : 0 );
            }
        };
    });
});