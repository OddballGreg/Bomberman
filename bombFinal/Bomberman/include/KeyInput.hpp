#pragma once

namespace Bomberman
{
  /**
   * @typedef	struct KeyInput
   *
   * @brief	Structure holding the state of keys on the keyboard that are related to the game.
   */

  typedef struct KeyInput
  {
    bool up, down, left, right, enter, camUp, camDown, camLeft, camRight, space, esc;

    KeyInput()
    {
      up = false;
      down = false;
      left = false;
      right = false;
      camUp = false;
      camDown = false;
      camLeft = false;
      camRight = false;
      enter = false;
      space = false;
      esc = false;
    }

  } KeyInput;

}
