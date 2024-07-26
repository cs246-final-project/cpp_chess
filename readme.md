Chess Game Readme

Overview

  This is a console-based chess game that supports both human and computer players. The game can be played between two human players, a human and a computer, or two computer players. It also supports setting up custom boards and includes features like resigning, castling, en passant, and promoting pawns.

Rules:
  It follows the basic rules of chess including castling, en passant, and promoting pawns. The game automatically detects checkmate and stalemate conditions.

Scoring:
  Win is 1 point for the winner and draw is 0.5 point for each player.

How to compile:
  Run the following command.
  ```make```

How to run:
  Run the following command.
  ```./chess```

Game Commands:
  Starting a Game.
    Use game command with two player types. Valid types are human, computer1, computer2, and computer3. For computer, higher number means smarter AI.
    ```game human computer1```

  Make a Move.
    Use move command to move. For computer's turn, just put move or m. For human's turn, put move command followed by position of current and destination. If it is a promotion move, also add type to promote. Valid promotions are 'Q', 'R', 'K', 'B'.
    ```move```
    ```m```
    ```move e2 e4```
    ```m E2 E4```
    ```move e2 e4 Q```

  Resign
    Use resign command to resign. Game terminates and opponent will get a score.
    ```resign```

  Quit
    Use quit command to terminate the program. cmd+d also works.
    ```quit```

  Commands about Setup Mode:
    Enter Setup Mode
      Enter setup mode with setup command. When entering the setup mode, you will start with an empty board and you can make your own starting board. It only works before the game starts.
      ```setup```

    Leave Setup Mode
      Leave setup mode with done command. It should be a valid board with one King for each team and no pawns can be in the first or last row. Also no kings should be in check.
      ```done```

    Add a Piece
      Add a piece in board with + command. It should be followed by Piece type and position.
      ```+ Q d1```

    Remove a Piece
      Add a piece in board with - command. It should be followed by position.
      ```- d1```

    Setting the Turn
      Use the = command followed by the color to set whose turn it is.
      ```= white```

Example Usage:
  ```
  game human computer1
  move e2 e4
  move e7 e5
  resign
  quit
  ```

Enjoy your chess!
