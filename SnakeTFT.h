#ifndef SnakeTFT_h
#define SnakeTFT_h

#include <Arduino.h>
#include <Elegoo_TFTLCD.h>

enum { UP, DOWN, LEFT, RIGHT };

enum
{
  BLACK   = 0x0000,
  WHITE   = 0xFFFF,
  RED     = 0xF800,
  YELLOW  = 0xFFE0,
  GREEN   = 0x07E0,
  CYAN    = 0x07FF,
  BLUE    = 0x001F,
  MAGENTA = 0xF81F,
};

typedef struct { int x; int y; int part; } snakePart_t;

class Snake
{
  private:
    int _CELL_SIZE = -1;

    Elegoo_TFTLCD *_tft = nullptr;

    enum { HEAD, BODY, TAIL };
    snakePart_t *_snake = nullptr;

  public:
    int score = 0;

    Snake(int, int);
    void begin(Elegoo_TFTLCD *tft);
    void append(snakePart_t part);
    void push(snakePart_t part);
    snakePart_t *pop();
    void draw(int color);
    void fillDisplay(int color);
};

class Joystick
{
  private:
    int _xPin = -1;
    int _yPin = -1;
    int _swPin = -1;

  public:
    Joystick(int x, int y, int sw);
    int getDirection();
};

#endif
