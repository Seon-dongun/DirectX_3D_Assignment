#pragma once

class SphereCollider : public Collider
{
public:
    SphereCollider(float radius = 1.0f, UINT stackCount = 8, UINT sliceCount = 16);
    ~SphereCollider();
        
    bool IsRayCollision(IN const Ray& ray, OUT Contact* contact) override;
    bool IsBoxCollision(BoxCollider* collider) override;
    bool IsSphereCollision(SphereCollider* collider) override;
    bool IsCapsuleCollision(CapsuleCollider* collider) override;

    float Radius() {
        return radius * max(GetGlobalScale().x,
            max(GetGlobalScale().y, GetGlobalScale().z));
    }

    float GetRadius() { return radius; }
private:
    void MakeMesh() override;

private:
    float radius;
    UINT stackCount, sliceCount;
};