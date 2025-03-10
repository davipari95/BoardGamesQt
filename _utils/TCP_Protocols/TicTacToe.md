# TCP/IP Communication Protocol - Tic Tac Toe

## Port ranges
From `49152` to `49161`.

## Excange string

### Server → Client

***

### Client → Server
#### `set-player-name <symbol> '<player_name>'`
Set the player name given the symbol in `<symbol>`, given between single quotes.

Symbol can be one of the following:
- `X`: uppercase "X", player that plays cross.
- `O`: uppercase "O", player that plays circle.

##### Answers
- `OK`: the username is successufully set.
- `NOK`: the username is not successufully set.

###### Example 1
Player X wants to set theyr username as 'Foo':
```text
>> set-player-name X 'Foo'
<< set-player-name OK
```