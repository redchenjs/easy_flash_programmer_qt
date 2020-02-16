/*
 * flash.h
 *
 *  Created on: 2019-08-18 19:00
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef FLASH_H
#define FLASH_H

#include <QtCore>
#include <QtSerialPort/QSerialPort>

#define OK           0
#define ERR_ARG     -1
#define ERR_FILE    -2
#define ERR_DEVICE  -3
#define ERR_REMOTE  -4

class FlashProgrammer : public QObject
{
    Q_OBJECT

public:
    void stop(void);
    void start(int argc, char *argv[]);

private slots:
    void error(QSerialPort::SerialPortError err);

private:
    QSerialPort *m_device = nullptr;
    size_t m_device_rsp = 0;

    QFile *data_fd = nullptr;
    uint32_t data_need = 0;
    uint32_t data_recv = 0;

    size_t rw_in_progress = 0;

    int open_device(const QString &devname);
    int close_device(void);

    void clear_response(void);
    size_t check_response(void);
    size_t wait_for_response(void);

    void process_data(void);
    int send_data(const char *data, uint32_t length);

    int erase_all(const QString &devname);
    int erase(const QString &devname, uint32_t addr, uint32_t length);
    int write(const QString &devname, uint32_t addr, uint32_t length, QString filename);
    int read(const QString &devname, uint32_t addr, uint32_t length, QString filename);
    int info(const QString &devname);

    void print_usage(char *appname);

signals:
    void finished(int err = OK);
};

#endif // FLASH_H
