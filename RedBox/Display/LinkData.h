/**
 * @file
 * @ingroup Display
 * @ingroup Physics
 */

#ifndef __LINK_DATA_H
#define __LINK_DATA_H

/**
 * Contains the information about a Link.
 * @ingroup Display
 * @ingroup Physics
 */
struct LinkData {
    float length;
    float frontMaxAngle;
    float frontMinAngle;
    float backMaxAngle;
    float backMinAngle;
    LinkData():length(0.0f), frontMaxAngle(0.0f), frontMinAngle(0.0f), backMaxAngle(0.0f), backMinAngle(0.0f) {}
    LinkData(float newLength, 
             float newFrontMaxAngle,
             float newFrontMinAngle,
             float newBackMaxAngle, 
             float newBackMinAngle):length(newLength), frontMaxAngle(newFrontMaxAngle), frontMinAngle(newFrontMinAngle), backMaxAngle(newBackMaxAngle), backMinAngle(newBackMinAngle) {}
};

#endif