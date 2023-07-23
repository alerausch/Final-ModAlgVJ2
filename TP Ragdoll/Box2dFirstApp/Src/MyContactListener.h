#pragma once
#include <box2d/box2d.h>
#include <iostream>
#include "Ragdoll.h"
class MyContactListener : public b2ContactListener {

public:
    MyContactListener() {};
    ~MyContactListener() {};

    // Se produce un contacto entre dos cuerpos
    virtual void BeginContact(b2Contact* contact);

    // El contacto entre los cuerpos ha finalizado      
    virtual void EndContact(b2Contact* contact) {};

    // Se ejecuta antes de resolver el contacto. 
    // Podemos evitar que se procese    
    virtual void PreSolve(b2Contact* contact,
        const b2Manifold* oldManifold) {};

    // Podemos obtener el impulso aplicado sobre los cuerpos en contacto
    virtual void PostSolve(b2Contact* contact,
        const b2ContactImpulse* impulse) {};
};