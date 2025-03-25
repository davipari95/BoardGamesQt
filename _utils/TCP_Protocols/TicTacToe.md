# TCP/IP Communication Protocol - Tic Tac Toe

## Excange string

### Client → Server

> ## `get-game\r\n`
> Retrieve the game that the server is managing.
> ### Answer
> Server will responds with `get-game\ntic-tac-toe\r\n`
> #### Example 1
> ```text
> >> get-game\r\n
> << get-game\r\ntic-tac-toe\r\n
> ```

> ## `get-player-info-sv\r\n`
> Retrieve all players informations from server.
> ### Answer
> Server will responds with `get-player-info-sv\n<cross_player_name>\n<circle_player_name>`, where:
> - `<cross_player_name>` is the nickname of the player that plays cross (`X`);
> - `<circle_player_name>` is the nickname of the player that plays circle (`O`).
> #### Example 1
> ```text
> >> get-player-info-sv\r\n
> << get-player-info-sv\nFoo Bar\nBar Foo\r\n
> ```

### Server → Client

> ## `client-disconnected\r\n`
> Aware all clients that someone is disconnected.
> ### Answer
> This command has no answer.

> ## `game-ready\r\n`
> Aware all clients that everything is ready for start game.
> ### Answer
> This command has no answer.

> ## `get-player-info\r\n`
> Retrieve all informations of the client: symbol and nickname.
> ### Answer
> Client will answer with `get-player-info\n<symbol>\n<nickname>\r\n`, where:
> - `<symbol>` is the symbol of the player:
>     - `X` for cross player.
>     - `O` for circle player.
> - `<nickname>`: the nickname of the player.
> #### Example 1
> Retrieve informations from client. The player is playing cross and the nickname is "Foo".
> ```text
> >> get-player-info\r\n
> << get-player-info\nX\nFoo
> ```