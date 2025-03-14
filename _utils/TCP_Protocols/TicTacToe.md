# TCP/IP Communication Protocol - Tic Tac Toe

## Port ranges
From `49152` to `49161`.

## Excange string

### Client → Server

> ## `get-game\r\n`
> Retrieve the game that the server is managing.
> ### Answer
> Server will responds with `get-game\r\ntic-tac-toe\r\n`
> #### Example 1
> ```text
> >> get-game\r\n
> << get-game\r\ntic-tac-toe\r\n

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
> Client will answer with `get-player-info\r\n<symbol>\r\n<nickname>\r\n`, where:
> - `<symbol>` is the symbol of the player:
>     - `X` for cross player.
>     - `O` for circle player.
> - `<nickname>`: the nickname of the player.
> #### Example 1
> Retrieve informations from client. The player is playing cross and the nickname is "Foo".
> ```text
> >> get-player-info\r\n
> << get-player-info\r\nX\r\nFoo
> ```