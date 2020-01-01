#include "stdafx.h"
#include "ESP.hpp"
#include "PlayerList.hpp"
#include "Signature.hpp"
#include "Render.hpp"

ESP::ESP()
{
}

ESP::~ESP()
{
}
struct Vec4
{
    float x, y, z, w;
};

bool ESP::WorldToScreen(Vector3 pos, Vector3& screen)
{

    float matrix[16];
    memcpy(&matrix, (float*)gSignature->dwViewMatrix, sizeof(matrix));
	float width = gRender->getWidth();
	float height = gRender->getHeight();

    Vec4 clipCoords;
    clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
    clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
    clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
    clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

    if (clipCoords.w < 0.1f)
        return false;

    Vector3 NDC;
    NDC.x = clipCoords.x / clipCoords.w;
    NDC.y = clipCoords.y / clipCoords.w;
    NDC.z = clipCoords.z / clipCoords.w;

    screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
    screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);
    return true;

}

void ESP::Run()
{
	if (gPlayerList->enemy.empty())
		return;

	for (auto e : gPlayerList->enemy)
	{
        Vector3 ePos = e->getPosition();
        Vector3 bonePos = e->getBonePosition(8);
        Vector3 screenPos, screenHeadPos;
        if (WorldToScreen(ePos, screenPos) && WorldToScreen(bonePos, screenHeadPos))
        {
            float boxHeight = screenPos.y - screenHeadPos.y;
            gRender->BorderBoxOutlined(screenHeadPos.x - boxHeight / 4.0f, screenHeadPos.y, boxHeight / 2.0f, boxHeight, 4.0f, WHITE, BLACK);
        }
	}

}

std::unique_ptr<ESP> gESP = std::make_unique<ESP>();