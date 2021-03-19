/**
 * SPDX-FileCopyrightText: 2016 Albert Vaca <albertvaka@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 */

#ifndef CLIPBOARDLISTENER_H
#define CLIPBOARDLISTENER_H

#include <QDateTime>
#include <QTimer>
#include <QObject>
#include <QClipboard>
#include <QGuiApplication>

/**
 * Wrapper around QClipboard, which emits clipboardChanged only when it really changed
 */

class ClipboardListener : public QObject
{
    Q_OBJECT

protected:
    ClipboardListener();
    void refreshContent(const QString &content);
    QString m_currentContent;

private:
    qint64 m_updateTimestamp = 0;

public:
    static ClipboardListener* instance();

    virtual void setText(const QString& content) = 0;

    QString currentContent();
    qint64 updateTimestamp();

Q_SIGNALS:
    void clipboardChanged(const QString& content);
};

class QClipboardListener : public ClipboardListener
{
public:
    QClipboardListener();

    void setText(const QString & content) override;

private:
#ifdef Q_OS_MAC
    QTimer m_clipboardMonitorTimer;
#endif
    void updateClipboard(QClipboard::Mode mode);
    QClipboard* clipboard;
};

class DataControl;

class WaylandClipboardListener : public ClipboardListener
{
public:
    WaylandClipboardListener();

    void setText(const QString & content) override;

private:
    void refresh(const QMimeData *mime);

    DataControl *m_dataControl;
};

#endif
