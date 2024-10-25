#pragma once

class BoxCollider : public Collider
{
public:
    struct ObbDesc
    {
        Vector3 pos;
        Vector3 axis[3];
        Vector3 halfSize;
    };

public:
    BoxCollider(Vector3 size = { 1, 1, 1 });
    ~BoxCollider() = default;
    
    bool IsRayCollision(IN const Ray& ray, OUT Contact* contact) override;
    bool IsBoxCollision(BoxCollider* collider) override;
    bool IsSphereCollision(SphereCollider* collider) override;
    bool IsCapsuleCollision(CapsuleCollider* collider) override;

    void GetObb(ObbDesc& obbDesc);

private:
    void MakeMesh() override;

    bool IsSeperateAxis(const Vector3& D, const Vector3& axis,
        const ObbDesc& box1, const ObbDesc& box2);

private:
    Vector3 size;
};