#include <headers.h>

int main()
{
    if( access( "storage.db", F_OK ) == 0 )
        connectDB();
    else
        createDbAndTables();
    // Sleep(1000);
    startApp();
    // adminSignup();
    return 0;
}
