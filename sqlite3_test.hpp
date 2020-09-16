#pragma once

#include <string>
using namespace std;

#include "sqlite3_test/sqlite3.h"

namespace sqlite3_618 {

    void test()
    {
        sqlite3* db = nullptr;
        auto ret = sqlite3_open(":memory:", &db);
        ret = sqlite3_db_config(db, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, NULL);
        ret = sqlite3_load_extension(db, "sqlite3_Extension_carry.dll", "sqlite3_carray_init", nullptr);
        ret = sqlite3_exec(db, "create table t_test ( \
                                id int primary key not null,\
                                age small int not null default 18)",
                           nullptr, nullptr, nullptr);

        char statementt[512]{ 0 };
        char* errmsg = nullptr;
        for (int i = 0; i < 100; i++)
        {
            sprintf(statementt, "insert into t_test values(%d,%d)", i, i);
            ret = sqlite3_exec(db, statementt, nullptr, nullptr, &errmsg);
            if (ret != SQLITE_OK)
            {
                printf("");
            }
        }

        sqlite3_stmt* stmt = nullptr;
        string query = "select * from t_test where id in carray($ptr, $n)";
        ret = sqlite3_prepare(db, query.c_str(), query.size(), &stmt, nullptr);
        int32_t* aaa = new int(5);
        for (int i = 0; i < 5; i++)
        {
            aaa[i] = i+5;
        }

        ret = sqlite3_bind_pointer(stmt, 1, (void*)aaa, "carray", [] (void*){});
        ret = sqlite3_bind_int(stmt, 2, 5);
        while (true)
        {
            auto ret = sqlite3_step(stmt);
            if(ret == SQLITE_DONE)
                break;
            printf("%d,%d", sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 1));
        }

        exit(0);
    }
}