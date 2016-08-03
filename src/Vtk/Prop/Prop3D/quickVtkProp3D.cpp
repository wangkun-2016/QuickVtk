#include "quickVtkProp3D.hpp"

namespace quick {

    namespace Vtk {

        Qml::Register::AbstractClass<Prop3D> Prop3D::Register;

        Prop3D::Prop3D(vtkSmartPointer<vtkProp3D> vtkObject) : Prop(vtkObject) {
            this->m_vtkObject = vtkProp3D::SafeDownCast(vtkObject);

            this->m_positionCb = [this] (Math::Vector3&& vector) {
                this->updatePosition(std::move(vector));
            };

            this->m_originCb = [this] (Math::Vector3&& vector) {
                this->updateOrigin(std::move(vector));
            };

            this->m_orientationCb = [this] (Math::Vector3&& vector) {
                this->updateOrientation(std::move(vector));
            };

            this->m_scaleCb = [this] (Math::Vector3&& vector) {
                this->updateScale(std::move(vector));
            };
        }

        auto Prop3D::updateScale(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetScale(vector.getValues().data());
            this->update();
        }

        auto Prop3D::updateOrigin(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetOrigin(vector.getValues().data());
            this->update();
        }

        auto Prop3D::updateOrientation(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetOrientation(vector.getValues().data());
            this->update();
        }

        auto Prop3D::updatePosition(Math::Vector3&& vector) -> void {
            this->m_vtkObject->SetPosition(vector.getValues().data());
            this->update();
        }

        auto Prop3D::setScale(Math::Vector3* vector) -> void {
            if (this->m_scale) {
                this->m_scale->removeCallback(std::move(this->m_scaleCb));
            }

            this->m_scale = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_scaleCb));
                this->updateScale(std::move(*vector));
            }

            emit this->scaleChanged();
        }

        auto Prop3D::getScale() -> Math::Vector3* {
            if (!this->m_scale) {
                auto scale = this->m_vtkObject->GetScale();
                this->setScale(new Math::Vector3(scale[0], scale[1], scale[2]));
            }

            return this->m_scale;
        }

        auto Prop3D::setPosition(Math::Vector3* vector) -> void {
            if (this->m_position) {
                this->m_position->removeCallback(std::move(this->m_positionCb));
            }

            this->m_position = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_positionCb));
                this->updatePosition(std::move(*vector));
            }

            emit this->positionChanged();
        }

        auto Prop3D::getPosition() -> Math::Vector3* {
            if (!this->m_position) {
                auto position = this->m_vtkObject->GetPosition();
                this->setPosition(new Math::Vector3(position[0], position[1], position[2]));
            }

            return this->m_position;
        }

        auto Prop3D::setOrientation(Math::Vector3* vector) -> void {
            if (this->m_orientation) {
                this->m_orientation->removeCallback(std::move(this->m_orientationCb));
            }

            this->m_orientation = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_orientationCb));
                this->updateOrientation(std::move(*vector));
            }

            emit this->orientationChanged();
        }

        auto Prop3D::getOrientation() -> Math::Vector3* {
            if (!this->m_orientation) {
                auto orientation = this->m_vtkObject->GetOrientation();
                this->setOrientation(new Math::Vector3(orientation[0], orientation[1], orientation[2]));
            }

            return this->m_orientation;
        }

        auto Prop3D::setOrigin(Math::Vector3* vector) -> void {
            if (this->m_origin) {
                this->m_origin->removeCallback(std::move(this->m_originCb));
            }

            this->m_origin = vector;

            if (vector) {
                vector->addCallback(std::move(this->m_originCb));
                this->updateOrigin(std::move(*vector));
            }

            emit this->orientationChanged();
        }

        auto Prop3D::getOrigin() -> Math::Vector3* {
            if (!this->m_origin) {
                auto origin = this->m_vtkObject->GetOrigin();
                this->setOrigin(new Math::Vector3(origin[0], origin[1], origin[2]));
            }

            return this->m_origin;
        }

        Prop3D::~Prop3D() {
            if (this->m_scale) {
                this->m_scale->removeCallback(std::move(this->m_scaleCb));
            }

            if (this->m_origin) {
                this->m_origin->removeCallback(std::move(this->m_originCb));
            }

            if (this->m_position) {
                this->m_position->removeCallback(std::move(this->m_positionCb));
            }

            if (this->m_orientation) {
                this->m_orientation->removeCallback(std::move(this->m_orientationCb));
            }
        }
    }
}