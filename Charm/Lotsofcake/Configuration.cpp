#include "Lotsofcake/Configuration.h"
#include "Core/XmlSerialization.h"

#include <QSettings>
#include <QUrl>

static const char *s_group = "httpconfig";
static const char *s_keyUsername = "username";
static const char *s_keyTimesheetUploadUrl = "timesheetUploadUrl";
static const char *s_keyProjectCodeDownloadUrl = "projectCodeDownloadUrl";
static const char *s_keyRestUrl = "restUrl";
static const char *s_keyLastStagedTimesheetUpload = "lastStagedTimesheetUpload";

static void setValueIfNotNull(QSettings *s, const QString &key, const QString &value)
{
    if (!value.isNull()) {
        s->setValue(key, value);
    } else {
        s->remove(key);
    }
}

bool Lotsofcake::Configuration::isConfigured() const
{
    return !username().isEmpty();
}

void Lotsofcake::Configuration::importFromTaskExport(const TaskExport &exporter)
{
    QSettings settings;
    settings.beginGroup(QLatin1String(s_group));
    setValueIfNotNull(&settings, QLatin1String(s_keyUsername),
                      exporter.metadata(QStringLiteral("username")));
    setValueIfNotNull(&settings, QLatin1String(s_keyTimesheetUploadUrl),
                      exporter.metadata(QStringLiteral("timesheet-upload-url")));
    setValueIfNotNull(&settings, QLatin1String(s_keyProjectCodeDownloadUrl),
                      exporter.metadata(QStringLiteral("project-code-download-url")));
    setValueIfNotNull(&settings, QLatin1String(s_keyRestUrl), exporter.metadata(QStringLiteral("rest-url")));
}

QString Lotsofcake::Configuration::username() const
{
    QSettings settings;
    settings.beginGroup(QLatin1String(s_group));
    return settings.value(QLatin1String(s_keyUsername)).toString();
}

QUrl Lotsofcake::Configuration::timesheetUploadUrl() const
{
    QSettings settings;
    settings.beginGroup(QLatin1String(s_group));
    QUrl url = settings.value(QLatin1String(s_keyTimesheetUploadUrl)).toUrl();
    url.setPath(QLatin1String("/KdabHome/apps/timesheets/rest/upload")); // TODO don't use hardcoded path
    return url;
}

QUrl Lotsofcake::Configuration::projectCodeDownloadUrl() const
{
    QSettings settings;
    settings.beginGroup(QLatin1String(s_group));
    return settings.value(QLatin1String(s_keyProjectCodeDownloadUrl)).toUrl();
}

QUrl Lotsofcake::Configuration::restUrl() const
{
    QSettings settings;
    settings.beginGroup(QLatin1String(s_group));
    return settings.value(QLatin1String(s_keyRestUrl)).toUrl();
}

QDate Lotsofcake::Configuration::lastStagedTimesheetUpload() const
{
    if (!m_lastStagedTimesheetUpload.set) {
        QSettings settings;
        settings.beginGroup(QLatin1String(s_group));
        m_lastStagedTimesheetUpload.date = settings.value(QLatin1String(s_keyLastStagedTimesheetUpload)).toDate();
        m_lastStagedTimesheetUpload.set = true;
    }

    return m_lastStagedTimesheetUpload.date;
}

void Lotsofcake::Configuration::setLastStagedTimesheetUpload(const QDate &date)
{
    QSettings settings;
    settings.beginGroup(QLatin1String(s_group));
    settings.setValue(QLatin1String(s_keyLastStagedTimesheetUpload), date);
    m_lastStagedTimesheetUpload.date = date;
    m_lastStagedTimesheetUpload.set = true;
}
