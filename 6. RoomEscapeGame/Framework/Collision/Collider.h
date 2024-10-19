#pragma once
#include "Objects/Basic/GameObject.h"

struct Ray
{
    Vector3 pos;
    Vector3 dir;

    Ray(Vector3 pos = Vector3(), Vector3 dir = Vector3::Forward())
        : pos(pos), dir(dir)
    {}
};

struct Contact
{
    Vector3 hitPoint;
    float distance;
};

class Collider : public GameObject
{
protected:
    enum Type
    {
        BOX, SPHERE, CAPSULE
    };

public:
    Collider();
    ~Collider();

    void Render();

    bool IsCollision(Collider* collider);

    virtual bool IsRayCollision(IN const Ray& ray, OUT Contact* contact = nullptr) = 0;
    virtual bool IsBoxCollision(class BoxCollider* collider) = 0;
    virtual bool IsSphereCollision(class SphereCollider* collider) = 0;
    virtual bool IsCapsuleCollision(class CapsuleCollider* collider) = 0;
    virtual void MakeMesh() = 0;

    void SetColor(Float4 color) { material->GetBuffer()->diffuse = color; }
    void SetColor(float r, float g, float b)
    {
        material->GetBuffer()->diffuse = { r, g, b, 1 };
    }
protected:
    Type type;
    Mesh<Vertex>* mesh;
};