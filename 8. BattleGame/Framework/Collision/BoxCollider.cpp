#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size) : size(size)
{
    type = BOX;

    MakeMesh();
    mesh->CreateMesh();
}

bool BoxCollider::IsRayCollision(IN const Ray& ray, OUT Contact* contact)
{
    ObbDesc box;
    GetObb(box);

    Vector3 min = box.halfSize * -1.0f;
    Vector3 max = box.halfSize;

    Vector3 delta = box.pos - ray.pos;
    Vector3 D = ray.dir.GetNormalized();

    float tMin = 0.0f;
    float tMax = FLT_MAX;

    FOR(3)
    {
        Vector3 axis = box.axis[i];
        float e = Vector3::Dot(axis, delta);
        float f = Vector3::Dot(axis, D);

        if (MATH->NearlyEqual(f, 0.0f))
        {
            if (min[i] > e || max[i] < e) return false;
        }
        else
        {
            float t1 = (e + min[i]) / f;
            float t2 = (e + max[i]) / f;

            if (t1 > t2) swap(t1, t2);

            if (t2 < tMax) tMax = t2;
            if (t1 > tMin) tMin = t1;

            if (tMin > tMax) return false;
        }
    }

    if (contact != nullptr)
    {
        contact->distance = tMin;
        contact->hitPoint = (Vector3)ray.pos + ray.dir * tMin;
    }

    return true;
}

bool BoxCollider::IsBoxCollision(BoxCollider* collider)
{
    ObbDesc box1, box2;
    GetObb(box1);
    collider->GetObb(box2);

    Vector3 D = box2.pos - box1.pos;

    FOR(3)
    {
        if (IsSeperateAxis(D, box1.axis[i], box1, box2)) return false;
        if (IsSeperateAxis(D, box2.axis[i], box1, box2)) return false;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (box1.axis[i] == box2.axis[j]) return true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Vector3 cross = Vector3::Cross(box1.axis[i], box2.axis[j]);
            if (IsSeperateAxis(D, cross, box1, box2)) return false;
        }
    }

    return true;
}

bool BoxCollider::IsSphereCollision(SphereCollider* collider)
{
    ObbDesc box;
    GetObb(box);

    Vector3 closestPointToSphere = box.pos;

    FOR(3)
    {
        Vector3 direction = collider->GetGlobalPosition() - box.pos;

        float length = Vector3::Dot(box.axis[i], direction);

        float mult = (length < 0.0f) ? -1.0f : 1.0f;

        length = min(abs(length), box.halfSize[i]);

        closestPointToSphere += box.axis[i] * length * mult;
    }

    float distance = (collider->GetGlobalPosition() - closestPointToSphere).Length();

    return distance <= collider->Radius();
}

bool BoxCollider::IsCapsuleCollision(CapsuleCollider* collider)
{
    return false;
}

void BoxCollider::GetObb(ObbDesc& obbDesc)
{
    obbDesc.pos = GetGlobalPosition();

    obbDesc.axis[0] = GetRight();
    obbDesc.axis[1] = GetUp();
    obbDesc.axis[2] = GetForward();

    obbDesc.halfSize = size * 0.5f * GetGlobalScale();
}

void BoxCollider::MakeMesh()
{
    Vector3 halfSize = size * 0.5f;

    vector<Vertex>& vertices = mesh->GetVertices();
    //Front
    vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z);
    vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z);
    vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z);
    vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z);

    //Back
    vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z);
    vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z);
    vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z);
    vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z);

    vector<UINT>& indices = mesh->GetIndices();

    indices =
    {
        0, 1, 1, 3, 3, 2, 2, 0,
        4, 5, 5, 7, 7, 6, 6, 4,
        0, 4, 1, 5, 3, 7, 2, 6
    };
}

bool BoxCollider::IsSeperateAxis(const Vector3& D, const Vector3& axis, const ObbDesc& box1, const ObbDesc& box2)
{
    float distance = abs(Vector3::Dot(D, axis));

    float a = 0.0f;
    float b = 0.0f;

    FOR(3)
    {
        Vector3 temp = box1.axis[i] * box1.halfSize[i];
        a += abs(Vector3::Dot(temp, axis));
        temp = box2.axis[i] * box2.halfSize[i];
        b += abs(Vector3::Dot(temp, axis));
    }

    return distance > a + b;
}
