#pragma once
#include "../util/Config.h"

class Widget
{
public:
	Widget(const Widget&) = delete;
	Widget(const Widget&&) = delete;
	Widget& operator=(const Widget&&) = delete;
	Widget& operator=(const Widget&) = delete;

	Widget() = default;

	virtual ~Widget() = default;

	/*!��ʼ���ؼ�
	 * ͨ�������ļ�����ʼ���ؼ�
	 * @note config �����ļ�
	 */
	virtual void init(const Config& config) {}

	/*!����¼�
	 * @param mouseX ���λ������ڿؼ�������
	 * @param mouseY ���λ������ڿؼ�������
	 */
	virtual void onClick(double mouseX, double mouseY) {}

	/*!��Ⱦ�¼�\n
	 * ÿ����Ⱦʱ����
	 */
	virtual void draw() {}

	/*!tick�¼�\n
	* ÿ0.02�����һ�Σ���Application�����
	* @note ���ܻ�����������ʱ���������
	*/
	virtual void tick() {}
};
