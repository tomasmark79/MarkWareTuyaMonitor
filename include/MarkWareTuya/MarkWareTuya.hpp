#ifndef __MARKWARETUYA_H__
#define __MARKWARETUYA_H__

#include <string>
// Library declaration

class MarkWareTuya
{
  public:
    MarkWareTuya();
    ~MarkWareTuya();
    void sendDeviceStatusRequest(const std::string &deviceIds, const std::string &accessToken);

  private:
};

#endif // __MARKWARETUYA_H__