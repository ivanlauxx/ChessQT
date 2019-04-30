#include "tests.h"

void Tests::testConstructor()
{
    QVERIFY2(testWindow.accs, "AccountManagement not created");
}

void Tests::testRegister()
{
    // Register username and password
    testAcc.registration("correctname", "password");

    // Refresh
    testAcc.loadList();

    // Login with username and password
    QVERIFY2(testAcc.login(testAcc.player1, "correctname", "password"), "login failed");
}

void Tests::testPlayGame()
{
    // Find buttons
    QPushButton *button1 = testWindow.findChild<QPushButton *>("gamePageButton");
    QPushButton *button2 = testWindow.findChild<QPushButton *>("pushButton");

    // Verify that objects do not exist yet (null pointers)
    QVERIFY2(!testWindow.scene, "scene already created");
    QVERIFY2(!testWindow.handler, "handler already created");

    // Click "Start", click "Play Game"
    QTest::mouseClick(button1, Qt::LeftButton);
    QTest::mouseClick(button2, Qt::LeftButton);

    // Verify that objects exist (non-null pointers)
    QVERIFY2(testWindow.scene, "scene not created");
    QVERIFY2(testWindow.handler, "handler not created");

    QTest::keyClick(&testWindow, Qt::Key_Escape, Qt::NoModifier);

    // Verify that objects have been deleted (null pointers)
    QVERIFY2(!testWindow.scene, "scene not deleted");
    QVERIFY2(!testWindow.handler, "handler not deleted");
}

//QTEST_MAIN(Tests);
