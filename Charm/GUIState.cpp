/*
  GUIState.cpp

  This file is part of Charm, a task-based time tracking application.

  Copyright (C) 2007-2015 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

  Author: Mirko Boehm <mirko.boehm@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QList>
#include <QSettings>

#include "Core/CharmConstants.h"

#include "Core/Task.h"
#include "GUIState.h"

GUIState::GUIState()
    : m_selectedTask( 0 )
{
}

const TaskIdList& GUIState::expandedTasks() const
{
    return m_expandedTasks;
}

TaskId GUIState::selectedTask() const
{
    return m_selectedTask;
}

void GUIState::setSelectedTask( TaskId task )
{
    m_selectedTask = task;
}

void GUIState::setExpandedTasks( const TaskIdList& tasks )
{
    m_expandedTasks = tasks;
}

void GUIState::saveTo( QSettings& settings )
{
    settings.setValue( MetaKey_MainWindowGUIStateSelectedTask, selectedTask() );
    // workaround for not getting QVariant serialization of TaskIdLists to work:
    QList<QVariant> variants;
    Q_FOREACH( TaskId v, expandedTasks() ) {
        variants << v;
    }
    settings.setValue( MetaKey_MainWindowGUIStateExpandedTasks, variants );
}

void GUIState::loadFrom( const QSettings& settings )
{
    if ( settings.contains( MetaKey_MainWindowGUIStateSelectedTask ) ) {
        setSelectedTask( settings.value( MetaKey_MainWindowGUIStateSelectedTask ).value<TaskId>() );;
    }
    if ( settings.contains( MetaKey_MainWindowGUIStateExpandedTasks ) ) {
        // workaround for not getting QVariant serialization of TaskIdLists to work:
        QList<QVariant> values( settings.value( MetaKey_MainWindowGUIStateExpandedTasks ).value<QList<QVariant> >() );
        TaskIdList ids;
        Q_FOREACH( QVariant variant, values ) {
            ids << variant.value<TaskId>();
        }
        setExpandedTasks( ids );
    }
}
