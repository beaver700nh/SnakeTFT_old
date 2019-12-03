#include "SnakeTFT.h"

Snake::Snake(int initialLength, int cellSize)
{
  int initialXPos = 8;
  int initialYPos = 5;
  _CELL_SIZE = cellSize;

  _snake = new snakePart_t[192];

  for (int i = 0; i < initialLength; ++i)
  {
    *(_snake+i) = { initialXPos-i, initialYPos,
    (i == 0 ? HEAD : (i == initialLength-1 ? TAIL : BODY)) };
  }

  Serial.begin(9600);
  Serial.print("Snake initialized.\n");
}

void Snake::begin(Elegoo_TFTLCD *tft)
{
  _tft = tft;

  _tft->reset();
  unsigned int id = _tft->readID();

  if (id == 0x0101)
  {
    Serial.print("Touchscreen has been found.\n");
  }

  _tft->begin(0x9341);
  _tft->setRotation(3);
  _tft->fillScreen(BLACK);
}

void Snake::append(snakePart_t newPart)
{
  snakePart_t *sp = _snake;

  while (++sp->part != TAIL)
  {
    /* empty */;
  }

  (sp++)->part = BODY;

  sp->x = newPart.x;
  sp->y = newPart.y;
  sp->part = TAIL;
}

void Snake::push(snakePart_t newPart)
{
  
}

snakePart_t *Snake::pop()
{
  
}

void Snake::draw(int color)
{
  snakePart_t *sp = _snake;
  
  do
  {
    switch (sp->part)
    {
      case HEAD:
        _tft->fillCircle(_CELL_SIZE*sp->x + _CELL_SIZE/2,
                         _CELL_SIZE*sp->y + _CELL_SIZE/2,
                         _CELL_SIZE/2, color);
        break;

      case BODY:
        _tft->fillRoundRect(_CELL_SIZE*sp->x, _CELL_SIZE*sp->y,
                            _CELL_SIZE, _CELL_SIZE, _CELL_SIZE/4, color);
        break;

      case TAIL:
        _tft->fillRoundRect(_CELL_SIZE*sp->x + _CELL_SIZE/4,
                            _CELL_SIZE*sp->y + _CELL_SIZE/4,
                            _CELL_SIZE/2, _CELL_SIZE/2, _CELL_SIZE/8, color);
        break;
    }
  }
  while(++sp->part != TAIL);

  Serial.print("Drawing...\n");
}

void Snake::fillDisplay(int color)
{
  
  _tft->fillScreen(color);
}

Joystick::Joystick(int xPin, int yPin, int swPin)
{
  if ((xPin < 14 || xPin > 19) ||
      (yPin < 14 || yPin > 19) ||
      (swPin < 2 || swPin > 19) ||
      (xPin == yPin) || 
      (yPin == swPin) ||
      (swPin == xPin))
  {
    return;
  }

  _xPin = xPin;
  _yPin = yPin;
  _swPin = swPin;

  pinMode(_xPin, INPUT);
  pinMode(_yPin, INPUT);
  pinMode(_swPin, INPUT);
}

int Joystick::getDirection()
{
  int posx = 0, posy = 0, negx = 0, negy = 0;

  posx = abs(analogRead(_xPin) - 512);
  posy = abs(analogRead(_yPin) - 512);
  negx = abs(analogRead(_xPin) - 512);
  negy = abs(analogRead(_yPin) - 512);

  return max(max(posx, posy), max(negx, negy));
}
