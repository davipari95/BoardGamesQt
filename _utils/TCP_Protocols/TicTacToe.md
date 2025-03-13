# TCP/IP Communication Protocol - Tic Tac Toe

## Port ranges
From `49152` to `49161`.

## Excange string

### Server → Client

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
> >> get-player-info
> << get-player-info\r\nX\r\nFoo
> ```