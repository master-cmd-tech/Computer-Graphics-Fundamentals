#include <iostream>

using namespace std;

void runRedTriangle();
void runBlueSquare();
void runPolygons();
void runCreative();
void runInteraction();
void runTransformations();

int main()
{
    int choice;

    while (true)
    {
        cout << "\n===== OpenGL Assignment =====\n";
        cout << "1 - Red Triangle\n";
        cout << "2 - Blue Square\n";
        cout << "3 - 2D Polygons\n";
        cout << "4 - Creative Picture\n";
        cout << "5 - Interaction / Animation\n";
        cout << "6 - 3D Transformations\n";
        cout << "7 - Exit\n";
        cout << "Choose: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            runRedTriangle();
            break;

        case 2:
            runBlueSquare();
            break;

        case 3:
            runPolygons();
            break;

        case 4:
            runCreative();
            break;

        case 5:
            runInteraction();
            break;

        case 6:
            runTransformations();
            break;

        case 7:
            return 0;

        default:
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}