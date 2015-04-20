#include "planutils.h"


void EightExpansion_init(EightExpansionUtil& e){
    Cell cell;
    //TOP LEFT
    cell.point.x = -1; cell.point.y = -1;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
    //TOP MIDDLE
    cell.point.x = 0; cell.point.y = -1;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
    //TOP RIGHT
    cell.point.x = 1; cell.point.y = -1;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
    //LEFT
    cell.point.x = -1;cell.point.y = 0;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
    //RIGHT
    cell.point.x = 1; cell.point.y = 0;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
    //BOTTOM RIGHT
    cell.point.x = -1; cell.point.y = 1;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
    //BOTTOM MIDDLE
    cell.point.x = 0; cell.point.y = 1;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
    //BOTTOM RIGHT
    cell.point.x = 1; cell.point.y = 1;
    cell.value = abs(cell.point.x)+abs(cell.point.y);
    e.push_back(cell);
}
