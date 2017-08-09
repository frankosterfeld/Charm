#ifndef LOTSOFCAKE_CONFIGURATION_H
#define LOTSOFCAKE_CONFIGURATION_H

#include <QDate>

class QString;
class QUrl;

class TaskExport;

namespace Lotsofcake {

class Configuration {
public:
    bool isConfigured() const;

    void importFromTaskExport(const TaskExport &exporter);

    QDate lastStagedTimesheetUpload() const;
    void setLastStagedTimesheetUpload(const QDate &date);

    QString username() const;
    QUrl timesheetUploadUrl() const;
    QUrl projectCodeDownloadUrl() const;
    QUrl restUrl() const;

private:
    mutable struct {
        bool set = false;
        QDate date;
    } m_lastStagedTimesheetUpload;
};

}

#endif
