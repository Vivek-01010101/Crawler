#include "../../include/PageStorage.h"
#include <sqlite3.h>
#include <iostream>

PageStorage::PageStorage()
{
    if (sqlite3_open("../Database/crawler.db", &db) != SQLITE_OK)
    {
        std::cerr << "Failed to open database.\n";
        return;
    }

    const char *sql =
        "CREATE TABLE IF NOT EXISTS pages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "url TEXT UNIQUE,"
        "depth INTEGER,"
        "html TEXT"
        ");";

    char *errMsg = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    
}

PageStorage::~PageStorage()
{
    sqlite3_close(db);
}

void PageStorage::storePage(const std::string &url,
                            const std::string &html,
                            int depth)
{
    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT OR IGNORE INTO pages(url, depth, html) "
        "VALUES(?, ?, ?);";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, url.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, depth);
    sqlite3_bind_text(stmt, 3, html.c_str(), -1, SQLITE_TRANSIENT);

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
}

std::string PageStorage::getPage(const std::string &url) const
{
    sqlite3_stmt *stmt;

    const char *sql =
        "SELECT html FROM pages WHERE url=?;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, url.c_str(), -1, SQLITE_TRANSIENT);

    std::string html;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char *text = sqlite3_column_text(stmt, 0);

        if (text)
            html = reinterpret_cast<const char *>(text);
    }

    sqlite3_finalize(stmt);

    return html;
}

bool PageStorage::hasPage(const std::string &url) const
{
    sqlite3_stmt *stmt;

    const char *sql =
        "SELECT 1 FROM pages WHERE url=? LIMIT 1;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, url.c_str(), -1, SQLITE_TRANSIENT);

    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return exists;
}

int PageStorage::pageCount() const
{
    sqlite3_stmt *stmt;

    const char *sql =
        "SELECT COUNT(*) FROM pages;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    int count = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);

    return count;
}