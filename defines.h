#ifndef DEFINES_H
#define DEFINES_H
namespace MapApl
{

enum CursorType{
    Default,        //Курсор по умолчанию (на всякий случай)
    PathCross,      //Инструмент Дистанция, ставим КП
    OpenHand        //Инструмент Сдвиг (перемещение)
};
enum ToolType{
    Path,           //Дистанция
    Ruler,          //Измерить
    Start,          //Пройти
    Move            //Сдвинуть
};
}
#endif // DEFINES_H
