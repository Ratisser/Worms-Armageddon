#pragma once
#include "EffectCircle.h"
#include "EffectElipse.h"
#include "EffectSmklt.h"
#include "EffectSmkdrk.h"
#include "EffectFlame.h"

#include "EffectBundleActor.h"
// �з� : 
// �뵵 : 
// ���� : 

namespace EffectBundle
{
	class Explosion
	{
	public:
		class Size25 : public EffectBundleActor
		{
		public:
			Size25(); // default constructer ����Ʈ ������
			~Size25(); // default destructer ����Ʈ �Ҹ���

		protected:		// delete constructer
			Size25(const Size25& _other) = delete; // default Copy constructer ����Ʈ ���������
			Size25(Size25&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

		private:		//delete operator
			Size25& operator=(const Size25& _other) = delete; // default Copy operator ����Ʈ ���� ������
			Size25& operator=(const Size25&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

		public:
			virtual void Start() final;
			virtual void UpdateBefore() final;
			virtual void Update() final;
			virtual void UpdateAfter() final;
			virtual void Render() final;
		};

		//size 50

		class Size50 : public EffectBundleActor
		{
		public:
			Size50(); // default constructer ����Ʈ ������
			~Size50(); // default destructer ����Ʈ �Ҹ���

		protected:		// delete constructer
			Size50(const Size50& _other) = delete; // default Copy constructer ����Ʈ ���������
			Size50(Size50&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

		private:		//delete operator
			Size50& operator=(const Size50& _other) = delete; // default Copy operator ����Ʈ ���� ������
			Size50& operator=(const Size50&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

		public:
			virtual void Start() final;
			virtual void UpdateBefore() final;
			virtual void Update() final;
			virtual void UpdateAfter() final;
			virtual void Render() final;
		};

		//size 75

		class Size75 : public EffectBundleActor
		{
		public:
			Size75(); // default constructer ����Ʈ ������
			~Size75(); // default destructer ����Ʈ �Ҹ���

		protected:		// delete constructer
			Size75(const Size75& _other) = delete; // default Copy constructer ����Ʈ ���������
			Size75(Size75&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

		private:		//delete operator
			Size75& operator=(const Size75& _other) = delete; // default Copy operator ����Ʈ ���� ������
			Size75& operator=(const Size75&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

		public:
			virtual void Start() final;
			virtual void UpdateBefore() final;
			virtual void Update() final;
			virtual void UpdateAfter() final;
			virtual void Render() final;
		};

		//size 100

		class Size100 : public EffectBundleActor
		{
		public:
			Size100(); // default constructer ����Ʈ ������
			~Size100(); // default destructer ����Ʈ �Ҹ���

		protected:		// delete constructer
			Size100(const Size100& _other) = delete; // default Copy constructer ����Ʈ ���������
			Size100(Size100&& _other) noexcept; // default RValue Copy constructer ����Ʈ RValue ���������

		private:		//delete operator
			Size100& operator=(const Size100& _other) = delete; // default Copy operator ����Ʈ ���� ������
			Size100& operator=(const Size100&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

		public:
			virtual void Start() final;
			virtual void UpdateBefore() final;
			virtual void Update() final;
			virtual void UpdateAfter() final;
			virtual void Render() final;
		};
	};
}
