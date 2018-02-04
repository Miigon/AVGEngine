#pragma once
#include "../util/DynamicObj.h"

class Widget :protected DynamicObj
{
public:
	Widget(const Widget&) = delete;
	Widget(const Widget&&) = delete;
	Widget& operator=(const Widget&&) = delete;
	Widget& operator=(const Widget&) = delete;

	Widget()
	{
		//������ɫ����
		addField("backgroundColor.r", FieldDouble);
		addField("backgroundColor.g", FieldDouble);
		addField("backgroundColor.b", FieldDouble);

		//�ؼ�����
		addField("name", FieldString);
	}

	virtual ~Widget() = default;

	/*!����¼�
	 * @param mouseX ���λ������ڿؼ�������
	 * @param mouseY ���λ������ڿؼ�������
	 */
	virtual void onClick(double mouseX, double mouseY) = 0;

	/*!��Ⱦ�¼�\n
	 * ÿ����Ⱦʱ����
	 */
	virtual void draw() = 0;

public:
	/*!tick�¼�\n
	* ÿ0.02�����һ�Σ���Application�����
	* @note ���ܻ�����������ʱ���������
	*/
	virtual void tick() = 0;
};