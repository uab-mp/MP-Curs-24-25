#pragma once

//! Enum de los botones del rat?

enum {

  //! Constante de control para uso interno
  BUTTON_NONE,                    // BUTTON_NONE tiene que ser >= 0 o se machacar?memoria

  //! Bot? principal del rat? (izquierdo en un rat? de 2 o 3 botones, o el ?nico en un Mac)
  BUTTON_1,

  //! Bot? principal del rat? (izquierdo en un rat? de 2 o 3 botones, o el ?nico en un Mac)
  BUTTON_LEFT = BUTTON_1,

  //! Bot? del medio en un rat? de 3 botones
  BUTTON_2,

  //! Bot? del medio en un rat? de 3 botones
  BUTTON_MIDDLE = BUTTON_2,

  //! Bot? derecho del rat?
  BUTTON_3,

  //! Bot? derecho del rat?
  BUTTON_RIGHT = BUTTON_3,

  //! Constante de control para uso interno, indica a cu?tos botones damos soporte
  MAX_NUM_POINTER_BUTTONS
} ;

//! \brief Estado del rat?

//! Estructura de datos donde guardamos el estado del rat? (posici?, movimiento, botones, etc)

struct T_MOUSE
{
  // Posici? actual del rat? en la ventana
  int x, y ;

  // Posici? del rat? en la ventana en el frame anterior
  int last_x, last_y ;

  // Desplazamiento que ha hecho el rat? desde el ?ltimo frame
  int offset_x, offset_y ;

  // Array de n?mero de botones que indica si est? pulsados (1) o no (0)
  int cnt[MAX_NUM_POINTER_BUTTONS] ;

  // Array de n?mero de botones que indica si han sido pulsados este frame (1) o no (0)
  int trg[MAX_NUM_POINTER_BUTTONS] ;

  // Indican si este frame se ha pulsado la rueda del rat?. La rueda no se puede mantener
  // pulsada, as?que no necesitamos distinguirlos como en el caso de los botones
  int bWheelUp, bWheelDown, bWheelLeft, bWheelRight ;
} ;

//! Esta funci? no est?pensada para usarse directamente. Avisa de que se acaba de soltar un bot? del rat?
void Mouse_ProcessButtonDown(int boton) ;

//! Esta funci? no est?pensada para usarse directamente. Avisa de que se acaba de soltar un bot? del rat?
void Mouse_ProcessButtonUp(int boton) ;

//! Esta funci? procesa los datos de haber movido la rueda del rat?
void Mouse_ProcessWheel(int wheelx, int wheely) ;

//! Inicializa la estructura de datos de rat? para poderla usar
void Mouse_Init() ;

//! Procesa los datos que tenemos del rat? para que luego podamos leer algo con sentido
void Mouse_Tick() ;

int Mouse_getX();

int Mouse_getY();

int Mouse_getButLeft();

int Mouse_getBtnLeft();
