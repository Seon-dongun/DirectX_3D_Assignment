#pragma once

class BoxCollider : public Collider
{
    // Collider��(��) ���� ��ӵ�
    bool IsRayCollision(IN const Ray& ray, OUT Contact* contact) override;
    bool IsBoxCollision(BoxCollider* collider) override;
    bool IsSphereCollision(SphereCollider* collider) override;
    bool IsCapsuleCollision(CapsuleCollider* collider) override;
    void MakeMesh() override;
};