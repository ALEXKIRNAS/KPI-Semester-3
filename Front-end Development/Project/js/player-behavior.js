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
                
				// Добаляю гравця через настройки options і зберігаю його
                var player = self.player = options.player;
                self.gameover = false;

               // Добаляю прослуховувач подій і реакію на натиск клавіш
                document.addEventListener('keydown', function( e ){
                    if (self.gameover){
                        return;
                    }
                    switch ( e.keyCode ){
                        case 38: // вверх
                            self.movePlayer();
                        break;
						case 40: // вниз
							 self.movePlayer( false );
                        break;
                        case 37: // вліво
                            player.turn( -1 );
                        break;
                        case 39: // вправо
                            player.turn( 1 );
                        break;
                        case 32: // пробіл
                            player.shoot();
                        break;
                    }
                    return false;
                });
				
				// Добаляю прослуховувач подій і реакію на відпускання клавіш
                document.addEventListener('keyup', function( e ){
                    if (self.gameover){
                        return;
                    }
                    switch ( e.keyCode ){
                        case 38: // вверх
                            self.movePlayer( false );
                        break;
						case 40: // вниз
							 self.movePlayer( false );
                        break;
                        case 37: // вліво
                            player.turn( 0 );
                        break;
                        case 39: // вправо
                            player.turn( 0 );
                        break;
                    }
                    return false;
                });
            },

            // Функція, яка автоматично викликається, коли скріпт підлючаєтсья до світу
            connect: function( world ){
                // Відслідковуємо події в світі
                world.on('collisions:detected', this.checkPlayerCollision, this);
                world.on('integrate:positions', this.behave, this);
            },

            // Функція, яка автоматично викликається, коли скріпт відключається від світу
            disconnect: function( world ){
				// Перестаємо відслідковувати події в світі
                world.off('collisions:detected', this.checkPlayerCollision);
                world.off('integrate:positions', this.behave);
            },

            // Провірка на зіткнення гравця з будь-чим
            checkPlayerCollision: function( data ){

                var self = this
                    ,world = self._world
                    ,collisions = data.collisions
                    ,col
                    ,player = this.player
                    ;

                for ( var i = 0, l = collisions.length; i < l; ++i ){
                    col = collisions[ i ];

					// відкидаємо зітнення сміття з сміттям і преевіряємо чи одним із тіл колізії є гравець
                    if ( col.bodyA.gameType !== 'debris' && 
                        col.bodyB.gameType !== 'debris' && 
                        (col.bodyA === player || col.bodyB === player)
                    ){
						
                        player.blowUp();
                        world.removeBehavior( this );
                        this.gameover = true;

                        // Закінчуємо гру
                        world.publish('lose-game');
                        return;
                    }
                }
            },

           // Переключення стану гравця (рухається чи ні)
            movePlayer: function( active ){

                if ( active === false ){
                    this.playerMove = false;
                    return;
                }
                this.playerMove = true;
            },

            behave: function( data ){

                // емулюємо рух, якщо playerMove === true
                this.player.thrust( this.playerMove === true ? 1 : 0 );
            }
        };
    });
});